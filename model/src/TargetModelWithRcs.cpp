#include "TargetModelWithRcs.h"
#include "TargetModelDAO.h"

TargetModelWithRcs TargetModelWithRcsDAO::getTargetWithRcsById(int targetId) {
    TargetModelWithRcs result;
    
    // 1. 获取目标机基本信息
    result.targetModel = TargetModelDAO::findById(targetId);
    
    // 2. 验证目标机是否存在
    if (result.targetModel.id != targetId) {
        // 目标机不存在时返回空对象
        return TargetModelWithRcs{};
    }
    
    // 3. 获取关联的所有RCS数据
    result.rcsDataList = RcsDataDAO::findByTargetId(targetId);
    
    return result;
}