#pragma once
#include "TargetModelDAO.h"
#include "RcsDataDAO.h"

// 组合数据结构：目标机模型 + 相关RCS数据
struct TargetModelWithRcs {
    TargetModel targetModel;          // 目标机模型信息
    std::vector<RcsData> rcsDataList; // 关联的RCS数据列表
};

class TargetModelWithRcsDAO {
public:
    // 根据目标机ID获取完整的目标机信息（包含所有RCS数据）
    static TargetModelWithRcs getTargetWithRcsById(int targetId);
};