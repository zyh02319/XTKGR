// FormationEvaluationController.cpp
#include "FormationEvaluationController.h"
#include "DetectionPerformanceView.h" // 包含距离计算函数

double FormationEvaluationController::evaluateFormation(
    int condition,
    const std::vector<RadarModel>& radars,
    const JammerModel* jammer,
    const TargetModel& target,
    const RcsData& rcs) 
{
    // 根据干扰条件选择算法
    switch (condition) {
    case 0: // 无干扰
        return FormationEvaluation::calculateDistanceWithoutJam(radars, rcs);
    case 1: // 有干扰
        if (jammer != nullptr) {
            return FormationEvaluation::calculateDistanceWithJam(radars, *jammer, target, rcs);
        } else {
            // 如果没有干扰机，按无干扰处理
            return FormationEvaluation::calculateDistanceWithoutJam(radars, rcs);
        }
    case 2: // 抗干扰
        if (jammer != nullptr) {
            return FormationEvaluation::calculateDistanceWithAntiJam(radars, *jammer, target, rcs);
        } else {
            // 如果没有干扰机，按无干扰处理
            return FormationEvaluation::calculateDistanceWithoutJam(radars, rcs);
        }
    default:
        return 0.0;
    }
}