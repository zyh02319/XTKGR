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
double SingleEvaluationController::calculateDistance(int condition, 
                                                   const RadarModel& radar, 
                                                   const JammerModel& jammer, 
                                                   const RcsData& rcs,
                                                   double distance) {  // 添加距离参数
    switch (condition) {
    case 0: // 无干扰
        return SingleEvaluation::calculateDistanceWithoutJam(radar, rcs);
    case 1: // 有干扰
        return SingleEvaluation::calculateDistanceWithJam(radar, jammer, rcs, distance);
    case 2: // 抗干扰
        return SingleEvaluation::calculateDistanceWithAntiJam(radar, jammer, rcs, distance);
    default:
        return 0.0;
    }
}