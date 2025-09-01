#ifndef SINGLEEVALUATION_H
#define SINGLEEVALUATION_H

#include "RadarModelDAO.h"
#include "JammerModelDAO.h"
#include "RcsDataDAO.h"
#include "ConstantValue.h"

class SingleEvaluation {
public:
    // 无干扰条件下的探测距离 (m)
    static double calculateDistanceWithoutJam(const RadarModel& radar, const RcsData& rcs);
    
    // 有干扰条件下的探测距离 (m) 
    static double calculateDistanceWithJam(const RadarModel& radar, const JammerModel& jammer, const RcsData& rcs, double jammerDistance);
    
    // 抗干扰条件下的探测距离 (m)
    static double calculateDistanceWithAntiJam(const RadarModel& radar, const JammerModel& jammer, const RcsData& rcs, double jammerDistance);
};

#endif // SINGLEEVALUATION_H