#include "SingleEvaluationController.h"

std::vector<RadarModel> SingleEvaluationController::getAllRadarModels() {
    std::vector<RadarModel> models;
    auto ids = RadarModelDAO::getAllRadarNamesAndIds();
    for (const auto& id_name : ids) {
        models.push_back(RadarModelDAO::findById(id_name.first));
    }
    return models;
}

std::vector<JammerModel> SingleEvaluationController::getAllJammerModels() {
    std::vector<JammerModel> models;
    auto ids = JammerModelDAO::getAllJammerNamesAndIds();
    for (const auto& id_name : ids) {
        models.push_back(JammerModelDAO::findById(id_name.first));
    }
    return models;
}

std::vector<TargetModel> SingleEvaluationController::getAllTargetModels() {
    std::vector<TargetModel> models;
    auto ids = TargetModelDAO::getAllTargetNamesAndIds();
    for (const auto& id_name : ids) {
        models.push_back(TargetModelDAO::findById(id_name.first));
    }
    return models;
}

std::vector<RcsData> SingleEvaluationController::getRcsDataByTargetId(int targetId) {
    return RcsDataDAO::findByTargetId(targetId);
}

// 保持向后兼容的版本
double SingleEvaluationController::calculateDistance(int condition, 
                                                   const RadarModel& radar, 
                                                   const JammerModel& jammer, 
                                                   const RcsData& rcs) {
    // 对于没有距离参数的版本，使用默认距离0
    return calculateDistance(condition, radar, jammer, rcs, 0.0, 0.0);
}

// 新版本，添加距离参数
double SingleEvaluationController::calculateDistance(int condition, 
                                                   const RadarModel& radar, 
                                                   const JammerModel& jammer, 
                                                   const RcsData& rcs,
                                                   double targetDistance,
                                                   double jammerDistance) {
    switch (condition) {
    case 0: // 无干扰
        return SingleEvaluation::calculateDistanceWithoutJam(radar, rcs);
    case 1: // 有干扰
        return SingleEvaluation::calculateDistanceWithJam(radar, jammer, rcs, jammerDistance);
    case 2: // 抗干扰
        return SingleEvaluation::calculateDistanceWithAntiJam(radar, jammer, rcs, jammerDistance);
    default:
        return 0.0;
    }
}