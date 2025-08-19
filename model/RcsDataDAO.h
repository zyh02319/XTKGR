//目标机RCS
#pragma once
#include "DataManager.h"
#include <vector>
#include <string>
#include <utility>
#include <QMetaType> // 添加包含

struct RcsData {
    int target_model_id;
    double azimuth;
    double elevation;
    double rcs_value;
};

// 确保在结构体定义后添加元类型声明
Q_DECLARE_METATYPE(RcsData)

// 然后定义DAO类
class RcsDataDAO {
public:
    static bool insert(const RcsData& data);
    static std::vector<std::pair<int, std::string>> getAllTargetRcsNamesAndIds();
    static std::vector<RcsData> findByTargetId(int targetId);
    static RcsData findByTargetIdAndAngles(int targetId, double azimuth, double elevation);
    static bool deleteByTargetIdAndAngles(int targetId, double azimuth, double elevation);
    static bool update(const RcsData& data);
    static bool deleteByTargetId(int targetId);
};