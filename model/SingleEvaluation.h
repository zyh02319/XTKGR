#ifndef SINGLEEVALUATION_H
#define SINGLEEVALUATION_H

#include "RadarModelDAO.h"   // 包含RadarModel结构体
#include "JammerModelDAO.h"  // 包含JammerModel结构体
#include "RcsDataDAO.h"      // 包含RcsData结构体
#include "ConstantValue.h"

class SingleEvaluation {
public:
    // 无干扰条件下的探测距离 (m)
    // static double calculateWithoutJam(const RadarModel& radar, const RcsData& rcs);
    static double calculateWithoutJam(const RadarModel& radar, const RcsData& rcs);
    
    // 有干扰条件下的探测距离 (m)
    // static double calculateWithJam(const RadarModel& radar, const JammerModel& jammer, const RcsData& rcs);
    static double calculateWithJam(const RadarModel& radar, const JammerModel& jammer, const RcsData& rcs, double distance);
    
    // 抗干扰条件下的探测距离 (m)
    // static double calculateWithAntiJam(const RadarModel& radar, const JammerModel& jammer, const RcsData& rcs);
    static double calculateWithAntiJam(const RadarModel& radar, const JammerModel& jammer, const RcsData& rcs, double distance);
};

#endif // SINGLEEVALUATION_H