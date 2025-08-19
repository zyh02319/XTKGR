#pragma once
#include <mysql/mysql.h>
#include <string>
//负责执行连接，查询，修改与断开的统一接口
class DataManager {
public:
    static DataManager& getInstance();
    
    bool connect();
    void disconnect();
    
    bool executeQuery(const std::string& query);
    MYSQL_RES* executeSelectQuery(const std::string& query);
    std::string escapeString(const std::string& input);
    double escapeDouble(double value);

private:
    DataManager();
    ~DataManager();
    DataManager(const DataManager&) = delete;
    DataManager& operator=(const DataManager&) = delete;
    
    MYSQL* conn;
};