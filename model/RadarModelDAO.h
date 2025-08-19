//雷达探测模型
#pragma once
#include "DataManager.h"
#include <vector>
#include <string>
#include <utility>
#include <QMetaType> // 添加包含

struct RadarModel {
    int id;
    std::string name;
    double wavelength;
    double power;
    double bandwidth;
    double gain;
    double loss_factor;
    double longitude;
    double latitude;
    double altitude;
};

// 确保在结构体定义后添加元类型声明
Q_DECLARE_METATYPE(RadarModel)

// 然后定义DAO类
class RadarModelDAO {
public:
    static bool insert(const RadarModel& model);
    static std::vector<std::pair<int, std::string>> getAllRadarNamesAndIds();
    static std::vector<RadarModel> findByName(const std::string& name);
    static RadarModel findById(int id);
    static bool deleteById(int id);
    static bool update(const RadarModel& model);
    static std::vector<std::pair<int, std::string>> searchRadarNamesAndIdsByName(const std::string& name);
};