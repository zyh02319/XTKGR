#ifndef SINGLEEVALUATIONCONTROLLER_H
#define SINGLEEVALUATIONCONTROLLER_H

#include "RadarModelDAO.h"
#include "JammerModelDAO.h"
#include "TargetModelDAO.h"
#include "RcsDataDAO.h"
#include "SingleEvaluation.h"
#include <vector>
#include <optional>

class SingleEvaluationController {
public:
    // 获取所有雷达模型
    static std::vector<RadarModel> getAllRadarModels();
    
    // 获取所有干扰机模型
    static std::vector<JammerModel> getAllJammerModels();
    
    // 获取所有目标模型
    static std::vector<TargetModel> getAllTargetModels();
    
    // 根据目标ID获取RCS数据
    static std::vector<RcsData> getRcsDataByTargetId(int targetId);
    
    // 计算探测距离 (保持向后兼容的版本)
    static double calculateDistance(int condition, 
                                   const RadarModel& radar, 
                                   const JammerModel& jammer, 
                                   const RcsData& rcs);
    
    // 计算探测距离 (新版本，添加距离参数)
    static double calculateDistance(int condition, 
                                   const RadarModel& radar, 
                                   const JammerModel& jammer, 
                                   const RcsData& rcs,
                                   double targetDistance,
                                   double jammerDistance);
};

#endif // SINGLEEVALUATIONCONTROLLER_H