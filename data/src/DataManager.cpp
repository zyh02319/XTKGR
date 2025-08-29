#include "DataManager.h"
#include "DBConfig.h"
#include <sstream>
#include <iostream>
//负责执行连接，查询，修改与断开的统一接口
DataManager::DataManager() : conn(nullptr) {}

DataManager::~DataManager() { 
    disconnect(); 
}

DataManager& DataManager::getInstance() {
    static DataManager instance;
    return instance;
}

//设置强制字符集
bool DataManager::connect() {

    conn = mysql_init(nullptr);
    if (!conn) return false;
    
    if (!mysql_real_connect(conn, DB_HOST.c_str(), DB_USER.c_str(), 
                          DB_PASS.c_str(), DB_NAME.c_str(), 
                          DB_PORT, nullptr, 0)) {
        std::cerr << "MySQL Connection Error: " << mysql_error(conn) << std::endl;
        conn = nullptr;
        return false;
    }
    
    // ===== 添加字符集设置 =====
    if (mysql_set_character_set(conn, "utf8mb4")) {
        std::cerr << "Failed to set charset: " << mysql_error(conn) << std::endl;
        mysql_close(conn);
        conn = nullptr;
        return false;
    }
    // ========================
    
    return true;
}

void DataManager::disconnect() {
    if (conn) {
        mysql_close(conn);
        conn = nullptr;
    }
}

// bool DataManager::executeQuery(const std::string& query) {
//     if (!conn) return false;
    
//     if (mysql_query(conn, query.c_str())) {
//         std::cerr << "Query Error: " << mysql_error(conn) << std::endl;
//         std::cerr << "Failed Query: " << query << std::endl;
//         return false;
//     }
//     return true;
// }

bool DataManager::executeQuery(const std::string& query) {
    if (!conn && !connect()) {  // 尝试重连
        std::cerr << "Database connection failed!" << std::endl;
        return false;
    }
    
    if (mysql_query(conn, query.c_str())) {
        std::cerr << "Query Error: " << mysql_error(conn) << std::endl;
        std::cerr << "Failed Query: " << query << std::endl;
        return false;
    }
    return true;
}

MYSQL_RES* DataManager::executeSelectQuery(const std::string& query) {
    if (!conn) return nullptr;
    
    if (mysql_query(conn, query.c_str())) {
        std::cerr << "Query Error: " << mysql_error(conn) << std::endl;
        return nullptr;
    }
    
    return mysql_store_result(conn);
}

std::string DataManager::escapeString(const std::string& input) {
    if (!conn) return input;
    
    char* output = new char[input.length() * 2 + 1];
    mysql_real_escape_string(conn, output, input.c_str(), input.length());
    std::string result(output);
    delete[] output;
    return result;
}

double DataManager::escapeDouble(double value) {
    return value;
}