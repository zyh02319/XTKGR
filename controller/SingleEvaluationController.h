#ifndef SINGLEEVALUATIONCONTROLLER_H
#define SINGLEEVALUATIONCONTROLLER_H

#include "RadarModelDAO.h"
#include "JammerModelDAO.h"
#include "TargetModelDAO.h"   // 包含TargetModel结构体
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
    
    // 计算探测距离
    static double calculateDistance(int condition, 
                                   const RadarModel& radar, 
                                   const JammerModel& jammer, 
                                   const RcsData& rcs);
    
    static double calculateDistance(int condition, 
                                   const RadarModel& radar, 
                                   const JammerModel& jammer, 
                                   const RcsData& rcs,
                                   double distance);  // 添加距离参数
};

#endif // SINGLEEVALUATIONCONTROLLER_H