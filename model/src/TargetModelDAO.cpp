//目标机模型的增删改查
#include "TargetModelDAO.h"
#include "DataManager.h"
#include <sstream>
#include <iostream>
#include "RcsDataDAO.h"  // 级联删除

bool TargetModelDAO::insert(const TargetModel& model) {
    std::stringstream ss;
    ss << "INSERT INTO target_model (name, target_type, longitude, latitude, altitude, position) "
       << "VALUES ('" << DataManager::getInstance().escapeString(model.name) << "', "
       << "'" << DataManager::getInstance().escapeString(model.target_type) << "', "
       << model.longitude << ", "
       << model.latitude << ", "
       << model.altitude << ", "
       << "ST_GeomFromText('POINT(" << model.longitude << " " << model.latitude << ")'))";
    
    return DataManager::getInstance().executeQuery(ss.str());
}
std::vector<std::pair<int, std::string>> TargetModelDAO::getAllTargetNamesAndIds() {
    std::vector<std::pair<int, std::string>> result;
    std::string query = "SELECT id, name FROM target_model";
    
    MYSQL_RES* res = DataManager::getInstance().executeSelectQuery(query);
    if (res) {
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res))) {
            result.push_back(std::make_pair(std::stoi(row[0]), row[1]));
        }
        mysql_free_result(res);
    }
    return result;
}

std::vector<TargetModel> TargetModelDAO::findByName(const std::string& name) {
    std::vector<TargetModel> result;
    std::string escapedName = DataManager::getInstance().escapeString(name);
    std::string query = "SELECT id, name, target_type, longitude, latitude, altitude "
                        "FROM target_model WHERE name = '" + escapedName + "'";
    
    MYSQL_RES* res = DataManager::getInstance().executeSelectQuery(query);
    if (res) {
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res))) {
            TargetModel model;
            model.id = std::stoi(row[0]);
            model.name = row[1] ? row[1] : "";
            model.target_type = row[2] ? row[2] : "";
            model.longitude = std::stod(row[3]);
            model.latitude = std::stod(row[4]);
            model.altitude = std::stod(row[5]);
            result.push_back(model);
        }
        mysql_free_result(res);
    }
    return result;
}

TargetModel TargetModelDAO::findById(int id) {
    TargetModel model;
    std::string query = "SELECT id, name, target_type, longitude, latitude, altitude "
                        "FROM target_model WHERE id = " + std::to_string(id);
    
    MYSQL_RES* res = DataManager::getInstance().executeSelectQuery(query);
    if (res) {
        MYSQL_ROW row = mysql_fetch_row(res);
        if (row) {
            model.id = std::stoi(row[0]);
            model.name = row[1] ? row[1] : "";
            model.target_type = row[2] ? row[2] : "";
            model.longitude = std::stod(row[3]);
            model.latitude = std::stod(row[4]);
            model.altitude = std::stod(row[5]);
        }
        mysql_free_result(res);
    }
    return model;
}

// bool TargetModelDAO::deleteById(int id) {
//     std::string query = "DELETE FROM target_model WHERE id = " + std::to_string(id);
//     return DataManager::getInstance().executeQuery(query);
// }
//级联删除
bool TargetModelDAO::deleteById(int id) {
    // 先删除关联的 RCS 数据
    if (!RcsDataDAO::deleteByTargetId(id)) {
        // 删除失败处理
        std::cerr << "Failed to delete RCS data for target ID: " << id << std::endl;
        return false;
    }
    
    // 再删除目标机
    std::string query = "DELETE FROM target_model WHERE id = " + std::to_string(id);
    return DataManager::getInstance().executeQuery(query);
}

bool TargetModelDAO::update(const TargetModel& model) {
    std::stringstream ss;
    ss << "UPDATE target_model SET "
       << "name = '" << DataManager::getInstance().escapeString(model.name) << "', "
       << "target_type = '" << DataManager::getInstance().escapeString(model.target_type) << "', "
       << "longitude = " << model.longitude << ", "
       << "latitude = " << model.latitude << ", "
       << "altitude = " << model.altitude << ", "
       << "position = ST_GeomFromText('POINT(" << model.longitude << " " << model.latitude << ")') "
       << "WHERE id = " << model.id;
    
    return DataManager::getInstance().executeQuery(ss.str());
}

std::vector<std::pair<int, std::string>> TargetModelDAO::findByNamePairs(const std::string& name) {
    std::vector<std::pair<int, std::string>> result;
    std::string escapedName = DataManager::getInstance().escapeString(name);
    std::string query = "SELECT id, name FROM target_model WHERE name LIKE '%" + escapedName + "%'";
    
    MYSQL_RES* res = DataManager::getInstance().executeSelectQuery(query);
    if (res) {
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res))) {
            result.push_back(std::make_pair(std::stoi(row[0]), row[1]));
        }
        mysql_free_result(res);
    }
    return result;
}