// FormationEvaluationController.cpp
#include "FormationEvaluationController.h"
#include "DetectionPerformanceView.h" // 包含距离计算函数

double FormationEvaluationController::evaluateFormation(
    int condition,
    const RadarModel& transmitter,
    const RadarModel& receiver,
    const JammerModel* jammer,
    const TargetModel& target,
    const RcsData& rcs) 
{
    double baseline = DetectionPerformanceView::calculateSpatialDistance(
        transmitter.longitude, transmitter.latitude, transmitter.altitude,
        receiver.longitude, receiver.latitude, receiver.altitude
    );
    
    // 根据干扰条件选择算法
    switch (condition) {
    case 0: // 无干扰 - 廖玉忠算法
        return FormationEvaluation::evaluateLiaoAlgorithm(
            transmitter, receiver, jammer, rcs, baseline, condition);
    case 1: // 有干扰 - 成天桢算法
    case 2: // 抗干扰 - 成天桢算法
        return FormationEvaluation::evaluateChengAlgorithm(
            transmitter, receiver, jammer, rcs, baseline, condition);
    default:
        return 0.0;
    }
}