//雷达探测模型的增删改查
#include "RadarModelDAO.h"
#include "DataManager.h"
#include <sstream>
#include <iostream>

// 按名称搜索雷达模型（只返回ID和名称）
std::vector<std::pair<int, std::string>> RadarModelDAO::searchRadarNamesAndIdsByName(const std::string& name) {
    std::vector<std::pair<int, std::string>> result;
    std::string escapedName = DataManager::getInstance().escapeString(name);
    std::string query = "SELECT id, name FROM radar_model WHERE name LIKE '%" + escapedName + "%'";
    
    MYSQL_RES* res = DataManager::getInstance().executeSelectQuery(query);
    if (res) {
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res))) {
            int id = row[0] ? std::stoi(row[0]) : 0;
            std::string name = row[1] ? row[1] : "";
            result.push_back(std::make_pair(id, name));
        }
        mysql_free_result(res);
    } else {
        std::cerr << "Failed to execute query: " << query << std::endl;
    }
    return result;
}

//增加
bool RadarModelDAO::insert(const RadarModel& model) {
    std::stringstream ss;
    ss << "INSERT INTO radar_model (name, wavelength, power, bandwidth, gain, loss_factor, longitude, latitude, altitude, position) "
       << "VALUES ('" << DataManager::getInstance().escapeString(model.name) << "', "
       << model.wavelength << ", "
       << model.power << ", "
       << model.bandwidth << ", "
       << model.gain << ", "
       << model.loss_factor << ", "
       << model.longitude << ", "
       << model.latitude << ", "
       << model.altitude << ", "
       << "ST_GeomFromText('POINT(" << model.longitude << " " << model.latitude << ")'))";
    
    return DataManager::getInstance().executeQuery(ss.str());
}
//获取名字和ID
std::vector<std::pair<int, std::string>> RadarModelDAO::getAllRadarNamesAndIds() {
    std::vector<std::pair<int, std::string>> result;
    std::string query = "SELECT id, name FROM radar_model";
    
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
std::vector<RadarModel> RadarModelDAO::findByName(const std::string& name) {
    std::vector<RadarModel> result;
    std::string escapedName = DataManager::getInstance().escapeString(name);
    std::string query = "SELECT id, name, wavelength, power, bandwidth, gain, loss_factor, longitude, latitude, altitude "
                        "FROM radar_model WHERE name = '" + escapedName + "'";
    
    MYSQL_RES* res = DataManager::getInstance().executeSelectQuery(query);
    if (res) {
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res))) {
            RadarModel model;
            model.id = std::stoi(row[0]);
            model.name = row[1] ? row[1] : "";
            model.wavelength = std::stod(row[2]);
            model.power = std::stod(row[3]);
            model.bandwidth = std::stod(row[4]);
            model.gain = std::stod(row[5]);
            model.loss_factor = std::stod(row[6]);
            model.longitude = std::stod(row[7]);
            model.latitude = std::stod(row[8]);
            model.altitude = std::stod(row[9]);
            result.push_back(model);
        }
        mysql_free_result(res);
    }
    return result;
}
//通过ID查找
RadarModel RadarModelDAO::findById(int id) {
    RadarModel model;
    std::string query = "SELECT id, name, wavelength, power, bandwidth, gain, loss_factor, longitude, latitude, altitude "
                        "FROM radar_model WHERE id = " + std::to_string(id);
    
    MYSQL_RES* res = DataManager::getInstance().executeSelectQuery(query);
    if (res) {
        MYSQL_ROW row = mysql_fetch_row(res);
        if (row) {
            model.id = std::stoi(row[0]);
            model.name = row[1] ? row[1] : "";
            model.wavelength = std::stod(row[2]);
            model.power = std::stod(row[3]);
            model.bandwidth = std::stod(row[4]);
            model.gain = std::stod(row[5]);
            model.loss_factor = std::stod(row[6]);
            model.longitude = std::stod(row[7]);
            model.latitude = std::stod(row[8]);
            model.altitude = std::stod(row[9]);
        }
        mysql_free_result(res);
    }
    return model;
}
//删除
bool RadarModelDAO::deleteById(int id) {
    std::string query = "DELETE FROM radar_model WHERE id = " + std::to_string(id);
    return DataManager::getInstance().executeQuery(query);
}
//更新
bool RadarModelDAO::update(const RadarModel& model) {
    std::stringstream ss;
    ss << "UPDATE radar_model SET "
       << "name = '" << DataManager::getInstance().escapeString(model.name) << "', "
       << "wavelength = " << model.wavelength << ", "
       << "power = " << model.power << ", "
       << "bandwidth = " << model.bandwidth << ", "
       << "gain = " << model.gain << ", "
       << "loss_factor = " << model.loss_factor << ", "
       << "longitude = " << model.longitude << ", "
       << "latitude = " << model.latitude << ", "
       << "altitude = " << model.altitude << ", "
       << "position = ST_GeomFromText('POINT(" << model.longitude << " " << model.latitude << ")') "
       << "WHERE id = " << model.id;
    
    return DataManager::getInstance().executeQuery(ss.str());
}