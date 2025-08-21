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
    // 无干扰条件下的编队评估
    static double calculateWithoutJam(const std::vector<RadarModel>& radars,
                                    const RcsData& rcs);
    
    // 有干扰条件下的编队评估
    static double calculateWithJam(const std::vector<RadarModel>& radars,
                                  const JammerModel& jammer,
                                  const RcsData& rcs);
    // 抗干扰条件下的编队评估
    static double calculateWithAntiJam(const std::vector<RadarModel>& radars,
                                      const JammerModel& jammer,
                                      const RcsData& rcs);
};