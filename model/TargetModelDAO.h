//目标机模型
#pragma once
#include "DataManager.h"
#include <vector>
#include <string>
#include <utility>
#include <QMetaType> // 添加包含

struct TargetModel {
    int id;
    std::string name;
    std::string target_type;
    double longitude;
    double latitude;
    double altitude;
    double heading;      // 航向(0-360度)
    double speed;        // 飞行速度(km/h)
};

// 确保在结构体定义后添加元类型声明
Q_DECLARE_METATYPE(TargetModel)

// 然后定义DAO类
class TargetModelDAO {
public:
    static bool insert(const TargetModel& model);
    static std::vector<std::pair<int, std::string>> getAllTargetNamesAndIds();
    static std::vector<TargetModel> findByName(const std::string& name);
    static TargetModel findById(int id);
    static bool deleteById(int id);
    static bool update(const TargetModel& model);
    static std::vector<std::pair<int, std::string>> findByNamePairs(const std::string& name);
};