//干扰机模型的增删改查
#include "JammerModelDAO.h"
#include "DataManager.h"
#include <iostream>
#include <sstream>
#include <iomanip>

// bool JammerModelDAO::insert(const JammerModel& model) {
//     std::stringstream ss;
//     ss << std::fixed << std::setprecision(6);  // 设置浮点数格式
    
//     ss << "INSERT INTO jammer_model (name, jamming_type, power, bandwidth, gain, longitude, latitude, altitude, position) "
//        << "VALUES ('" << DataManager::getInstance().escapeString(model.name) << "', "
//        << "'" << DataManager::getInstance().escapeString(model.jamming_type) << "', "
//        << model.power << ", "
//        << model.bandwidth << ", "
//        << model.gain << ", "
//        << model.longitude << ", "
//        << model.latitude << ", "
//        << model.altitude << ", "
//        << "ST_GeomFromText('POINT(" 
//        << std::fixed << std::setprecision(6) << model.longitude << " " 
//        << std::fixed << std::setprecision(6) << model.latitude << ")'))";
    
//     return DataManager::getInstance().executeQuery(ss.str());
// }
//增加
bool JammerModelDAO::insert(const JammerModel& model) {
    DataManager& dm = DataManager::getInstance();
    
    std::stringstream ss;
    ss << "INSERT INTO jammer_model (name, jamming_type, power, bandwidth, gain, longitude, latitude, altitude, position, heading, speed) "
       << "VALUES ('" << dm.escapeString(model.name) << "', "
       << "'" << dm.escapeString(model.jamming_type) << "', "  // 确保转义
       << model.power << ", "
       << model.bandwidth << ", "
       << model.gain << ", "
       << model.longitude << ", "
       << model.latitude << ", "
       << model.altitude << ", "
        << "ST_GeomFromText('POINT(" 
        << std::fixed << std::setprecision(6) << model.longitude << " " 
        << std::fixed << std::setprecision(6) << model.latitude << ")'), "
       << model.heading << ", "
       << model.speed << ")";
    
    std::string query = ss.str();
    std::cout << "Executing query: " << query << std::endl;  // 添加调试输出
    return dm.executeQuery(query);
}
//获取名字与ID
std::vector<std::pair<int, std::string>> JammerModelDAO::getAllJammerNamesAndIds() {
    std::vector<std::pair<int, std::string>> result;
    std::string query = "SELECT id, name FROM jammer_model";
    
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
//通过名字查找
std::vector<JammerModel> JammerModelDAO::findByName(const std::string& name) {
    std::vector<JammerModel> result;
    std::string escapedName = DataManager::getInstance().escapeString(name);
    std::string query = "SELECT id, name, jamming_type, power, bandwidth, gain, longitude, latitude, altitude, heading, speed "
                        "FROM jammer_model WHERE name = '" + escapedName + "'";
    
    MYSQL_RES* res = DataManager::getInstance().executeSelectQuery(query);
    if (res) {
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res))) {
            JammerModel model;
            model.id = std::stoi(row[0]);
            model.name = row[1] ? row[1] : "";
            model.jamming_type = row[2] ? row[2] : "";
            model.power = std::stod(row[3]);
            model.bandwidth = std::stod(row[4]);
            model.gain = std::stod(row[5]);
            model.longitude = std::stod(row[6]);
            model.latitude = std::stod(row[7]);
            model.altitude = std::stod(row[8]);
            model.heading = row[9] ? std::stod(row[9]) : 0.0;
            model.speed = row[10] ? std::stod(row[10]) : 0.0;
            result.push_back(model);
        }
        mysql_free_result(res);
    }
    return result;
}
//通过ID进行查找
JammerModel JammerModelDAO::findById(int id) {
    JammerModel model;
    std::string query = "SELECT id, name, jamming_type, power, bandwidth, gain, longitude, latitude, altitude, heading, speed "
                        "FROM jammer_model WHERE id = " + std::to_string(id);
    
    MYSQL_RES* res = DataManager::getInstance().executeSelectQuery(query);
    if (res) {
        MYSQL_ROW row = mysql_fetch_row(res);
        if (row) {
            model.id = std::stoi(row[0]);
            model.name = row[1] ? row[1] : "";
            model.jamming_type = row[2] ? row[2] : "";
            model.power = std::stod(row[3]);
            model.bandwidth = std::stod(row[4]);
            model.gain = std::stod(row[5]);
            model.longitude = std::stod(row[6]);
            model.latitude = std::stod(row[7]);
            model.altitude = std::stod(row[8]);
            model.heading = row[9] ? std::stod(row[9]) : 0.0;
            model.speed = row[10] ? std::stod(row[10]) : 0.0;
        }
        mysql_free_result(res);
    }
    return model;
}
// 按名称搜索，只返回名称和ID
std::vector<std::pair<int, std::string>> JammerModelDAO::searchJammerNamesAndIdsByName(const std::string& name) {
    std::vector<std::pair<int, std::string>> result;
    std::string escapedName = DataManager::getInstance().escapeString(name);
    std::string query = "SELECT id, name FROM jammer_model WHERE name LIKE '%" + escapedName + "%'";
    
    MYSQL_RES* res = DataManager::getInstance().executeSelectQuery(query);
    if (res) {
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res))) {
            result.push_back(std::make_pair(std::stoi(row[0]), row[1] ? row[1] : ""));
        }
        mysql_free_result(res);
    }
    return result;
}
//删除
bool JammerModelDAO::deleteById(int id) {
    std::string query = "DELETE FROM jammer_model WHERE id = " + std::to_string(id);
    return DataManager::getInstance().executeQuery(query);
}
//更新
bool JammerModelDAO::update(const JammerModel& model) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(6);  // 设置浮点数格式
    
    ss << "UPDATE jammer_model SET "
       << "name = '" << DataManager::getInstance().escapeString(model.name) << "', "
       << "jamming_type = '" << DataManager::getInstance().escapeString(model.jamming_type) << "', "
       << "power = " << model.power << ", "
       << "bandwidth = " << model.bandwidth << ", "
       << "gain = " << model.gain << ", "
       << "longitude = " << model.longitude << ", "
       << "latitude = " << model.latitude << ", "
       << "altitude = " << model.altitude << ", "
       << "position = ST_GeomFromText('POINT(" 
       << std::fixed << std::setprecision(6) << model.longitude << " " 
       << std::fixed << std::setprecision(6) << model.latitude << ")'), "
       << "heading = " << model.heading << ", "
       << "speed = " << model.speed << " "
       << "WHERE id = " << model.id;
    
    return DataManager::getInstance().executeQuery(ss.str());
}