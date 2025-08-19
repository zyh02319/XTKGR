//用于增删改查model的控制器
#pragma once
#include <vector>
#include <string>
#include "JammerModelDAO.h"
#include "RadarModelDAO.h" 
#include "TargetModelDAO.h"      // 添加目标模型DAO
#include "RcsDataDAO.h"          // 添加RCS数据DAO
#include "TargetModelWithRcs.h"  // 添加目标模型与RCS组合

class ModelManageController {
public:
// 干扰机模型方法
    static bool createJammerModel(const JammerModel& model);
    static bool updateJammerModel(const JammerModel& model);
    static bool deleteJammerModel(int id);
    // static JammerModel getJammerModelById(int id);
    // static std::vector<JammerModel> getAllJammerModels();
    // static std::vector<JammerModel> searchJammerModelsByName(const std::string& name);

    // 修改返回类型，只获取名称和ID
    static std::vector<std::pair<int, std::string>> getAllJammerNamesAndIds();
    // 添加新方法，按ID获取完整模型
    static JammerModel getJammerModelById(int id);
    // 修改搜索方法，只返回名称和ID
    static std::vector<std::pair<int, std::string>> searchJammerModelsByName(const std::string& name);

// 探测模型方法
    static bool createRadarModel(const RadarModel& model);
    static bool updateRadarModel(const RadarModel& model);
    static bool deleteRadarModel(int id);
    static RadarModel getRadarModelById(int id);
    static std::vector<std::pair<int, std::string>> getAllRadarNamesAndIds();
    static std::vector<std::pair<int, std::string>> searchRadarModelsByName(const std::string& name);
// 目标模型方法
// static bool createTargetModel(const TargetModel& model);
// static bool updateTargetModel(const TargetModel& model);
// static bool deleteTargetModel(int id);
// static TargetModel getTargetModelById(int id);
// static std::vector<std::pair<int, std::string>> getAllTargetNamesAndIds();
// static std::vector<std::pair<int, std::string>> searchTargetModelsByName(const std::string& name);
// static TargetModelWithRcs getTargetModelWithRcsById(int id); // 获取完整的目标模型（含RCS数据）
// RCS数据方法
// static bool createRcsData(const RcsData& data);
// static bool updateRcsData(const RcsData& data);
// static bool deleteRcsData(int targetId, double azimuth, double elevation);
// static RcsData getRcsData(int targetId, double azimuth, double elevation);
// static std::vector<RcsData> getRcsDataByTargetId(int targetId);
 // ========== 目标模型方法 ==========
    static bool createTargetModel(const TargetModel& model);
    static bool updateTargetModel(const TargetModel& model);
    static bool deleteTargetModel(int id);
    static TargetModel getTargetModelById(int id);
    static std::vector<std::pair<int, std::string>> getAllTargetNamesAndIds();
    static std::vector<std::pair<int, std::string>> searchTargetModelsByName(const std::string& name);
    static TargetModelWithRcs getTargetModelWithRcsById(int id);

    // ========== RCS数据方法 ==========
    static bool createRcsData(const RcsData& data);
    static bool updateRcsData(const RcsData& data);
    static bool deleteRcsData(int targetId, double azimuth, double elevation);
    static RcsData getRcsData(int targetId, double azimuth, double elevation);
    static std::vector<RcsData> getRcsDataByTargetId(int targetId);
};