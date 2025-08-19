//目标机RCS的增删改查
#include "RcsDataDAO.h"
#include "DataManager.h"
#include <sstream>

bool RcsDataDAO::insert(const RcsData& data) {
    std::stringstream ss;
    ss << "INSERT INTO rcs_table (target_model_id, azimuth, elevation, rcs_value) "
       << "VALUES (" << data.target_model_id << ", "
       << data.azimuth << ", "
       << data.elevation << ", "
       << data.rcs_value << ")";
    
    return DataManager::getInstance().executeQuery(ss.str());
}

std::vector<std::pair<int, std::string>> RcsDataDAO::getAllTargetRcsNamesAndIds() {
    std::vector<std::pair<int, std::string>> result;
    std::string query = "SELECT DISTINCT t.id, t.name "
                        "FROM rcs_table r "
                        "JOIN target_model t ON r.target_model_id = t.id";
    
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

std::vector<RcsData> RcsDataDAO::findByTargetId(int targetId) {
    std::vector<RcsData> result;
    std::string query = "SELECT target_model_id, azimuth, elevation, rcs_value "
                        "FROM rcs_table WHERE target_model_id = " + std::to_string(targetId);
    
    MYSQL_RES* res = DataManager::getInstance().executeSelectQuery(query);
    if (res) {
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res))) {
            RcsData data;
            data.target_model_id = std::stoi(row[0]);
            data.azimuth = std::stod(row[1]);
            data.elevation = std::stod(row[2]);
            data.rcs_value = std::stod(row[3]);
            result.push_back(data);
        }
        mysql_free_result(res);
    }
    return result;
}

RcsData RcsDataDAO::findByTargetIdAndAngles(int targetId, double azimuth, double elevation) {
    RcsData data;
    std::string query = "SELECT target_model_id, azimuth, elevation, rcs_value "
                        "FROM rcs_table WHERE target_model_id = " + std::to_string(targetId) +
                        " AND azimuth = " + std::to_string(azimuth) +
                        " AND elevation = " + std::to_string(elevation);
    
    MYSQL_RES* res = DataManager::getInstance().executeSelectQuery(query);
    if (res) {
        MYSQL_ROW row = mysql_fetch_row(res);
        if (row) {
            data.target_model_id = std::stoi(row[0]);
            data.azimuth = std::stod(row[1]);
            data.elevation = std::stod(row[2]);
            data.rcs_value = std::stod(row[3]);
        }
        mysql_free_result(res);
    }
    return data;
}

bool RcsDataDAO::deleteByTargetIdAndAngles(int targetId, double azimuth, double elevation) {
    std::string query = "DELETE FROM rcs_table WHERE target_model_id = " + std::to_string(targetId) +
                        " AND azimuth = " + std::to_string(azimuth) +
                        " AND elevation = " + std::to_string(elevation);
    return DataManager::getInstance().executeQuery(query);
}

bool RcsDataDAO::update(const RcsData& data) {
    std::stringstream ss;
    ss << "UPDATE rcs_table SET "
       << "rcs_value = " << data.rcs_value << " "
       << "WHERE target_model_id = " << data.target_model_id << " "
       << "AND azimuth = " << data.azimuth << " "
       << "AND elevation = " << data.elevation;
    
    return DataManager::getInstance().executeQuery(ss.str());
}
bool RcsDataDAO::deleteByTargetId(int targetId) {
    std::string query = "DELETE FROM rcs_table WHERE target_model_id = " + std::to_string(targetId);
    return DataManager::getInstance().executeQuery(query);
}