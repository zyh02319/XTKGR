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
    static double calculateDistanceWithoutJam(const std::vector<RadarModel>& radars,
                                    const RcsData& rcs);
    
    // 有干扰条件下的编队评估
    static double calculateDistanceWithJam(const std::vector<RadarModel>& radars,
                                  const JammerModel& jammer,
                                  const TargetModel& target,
                                  const RcsData& rcs);
    // 抗干扰条件下的编队评估
    static double calculateDistanceWithAntiJam(const std::vector<RadarModel>& radars,
                                      const JammerModel& jammer,
                                      const TargetModel& target,
                                      const RcsData& rcs);
private:
    // 引入空间距离计算辅助函数
    static double calculateSpatialDistance(
        double lon1, double lat1, double alt1, 
        double lon2, double lat2, double alt2);
};