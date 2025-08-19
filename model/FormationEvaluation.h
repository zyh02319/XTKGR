// FormationEvaluation.h
#pragma once
#include "RadarModelDAO.h"
#include "JammerModelDAO.h"
#include "TargetModelDAO.h"
#include "RcsDataDAO.h"
#include "ConstantValue.h"
#include <cmath>

class FormationEvaluation {
public:
    // 算法1：成天桢论文算法
    static double evaluateChengAlgorithm(
        const RadarModel& transmitter,
        const RadarModel& receiver,
        const JammerModel* jammer,
        const RcsData& rcs,
        double baseline,
        int condition);
    
    // 算法2：廖玉忠论文算法
    static double evaluateLiaoAlgorithm(
        const RadarModel& transmitter,
        const RadarModel& receiver,
        const JammerModel* jammer,
        const RcsData& rcs,
        double baseline,
        int condition);
};