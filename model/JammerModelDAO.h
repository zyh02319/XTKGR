// 干扰机模型的增删改查
#pragma once
#include "DataManager.h"
#include <vector>
#include <string>
#include <utility>
#include <QMetaType> // 添加包含

struct JammerModel {
    int id;
    std::string name;
    std::string jamming_type;
    double power;
    double bandwidth;
    double gain;
    double longitude;
    double latitude;
    double altitude;
    double heading;      // 航向(0-360度)
    double speed;        // 飞行速度(km/h)
};

// 确保在结构体定义后添加元类型声明
Q_DECLARE_METATYPE(JammerModel)

// 然后定义DAO类
class JammerModelDAO {
public:
    static bool insert(const JammerModel& model);
    static std::vector<std::pair<int, std::string>> getAllJammerNamesAndIds();
    static std::vector<JammerModel> findByName(const std::string& name);
    static JammerModel findById(int id);
    static bool deleteById(int id);
    static bool update(const JammerModel& model);
    static std::vector<std::pair<int, std::string>> searchJammerNamesAndIdsByName(const std::string& name);
};
