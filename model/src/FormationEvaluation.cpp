// FormationEvaluation.cpp
#include "FormationEvaluation.h"

// 引入空间距离计算辅助函数
double FormationEvaluation::calculateSpatialDistance(
    double lon1, double lat1, double alt1, 
    double lon2, double lat2, double alt2){
    // 地球半径（米）
    const double R = 6371000.0;
    
    // 将经纬度转换为弧度
    double lat1Rad = lat1 * ConstantValue::PI / 180.0;
    double lon1Rad = lon1 * ConstantValue::PI / 180.0;
    double lat2Rad = lat2 * ConstantValue::PI / 180.0;
    double lon2Rad = lon2 * ConstantValue::PI / 180.0;
    
    // 计算差值
    double dLat = lat2Rad - lat1Rad;
    double dLon = lon2Rad - lon1Rad;
    
    // Haversine公式计算球面距离
    double a = sin(dLat/2) * sin(dLat/2) +
               cos(lat1Rad) * cos(lat2Rad) * sin(dLon/2) * sin(dLon/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    double distance = R * c;
    
    // 考虑高度差（直角坐标）
    double dAlt = alt2 - alt1;
    return sqrt(distance * distance + dAlt * dAlt);
}

//无干扰条件下
double FormationEvaluation::calculateDistanceWithoutJam(const std::vector<RadarModel>& radars,
                                                  const RcsData& rcs) {
    // 文档依据：无干扰时，目标回波受噪声限制，多站信号叠加增益基于目标回波互不相关特性
    const RadarModel& mainRadar = radars[0];
    
    // 单位转换：KW -> W
    double P_t_main = mainRadar.power * 1000;
    
    // dB转线性值（天线增益影响目标回波幅度，文档无干扰模型）
    double G_t_main = ConstantValue::dBToLinear(mainRadar.gain);
    // 无干扰时需计算天线增益的平方（双程雷达方程）
    double G_t_squared = G_t_main * G_t_main;

    // 目标RCS（取主站观测值）
    double sigma = rcs.rcs_value;

    // 多站目标信号叠加增益（无干扰时，目标回波功率叠加需考虑天线增益平方项）
    double targetGain = 1.0; // 主站基础增益
    for (size_t i = 1; i < radars.size(); ++i) {
        double P_t_sub = radars[i].power * 1000;
        double G_t_sub = ConstantValue::dBToLinear(radars[i].gain);
        double G_t_sub_squared = G_t_sub * G_t_sub;
        targetGain += (P_t_sub * G_t_sub_squared) / (P_t_main * G_t_squared);
    }

    // 雷达波长（m）
    double lambda = mainRadar.wavelength;
    double lambda_squared = lambda * lambda;

    // 分子：无干扰条件下的目标信号功率相关项（含双程传播的天线增益平方和波长平方）
    double numerator = P_t_main * G_t_squared * lambda_squared * sigma * targetGain;

    // 分母：双程传播损耗、系统损耗及最小可检测信号功率
    double denominator = pow(4 * ConstantValue::PI, 3) 
                       * ConstantValue::L 
                       * ConstantValue::S_min;

    // 四次方根计算（距离与功率的四次方反比关系）
    return pow(numerator / denominator, 0.25);
}

//有干扰条件下
double FormationEvaluation::calculateDistanceWithJam(const std::vector<RadarModel>& radars,
                                                const JammerModel& jammer,
                                                const TargetModel& target,
                                                const RcsData& rcs) {
    // 改进：使用空间距离进行计算，而不是固定增益
    double totalTargetSignalPower = 0.0;
    double totalJammerSignalPower = 0.0;

    for (const auto& radar : radars) {
        // 计算雷达到目标和雷达到干扰机的距离
        double targetDistance = calculateSpatialDistance(radar.longitude, radar.latitude, radar.altitude,
                                                         target.longitude, target.latitude, target.altitude);
        double jammerDistance = calculateSpatialDistance(radar.longitude, radar.latitude, radar.altitude,
                                                         jammer.longitude, jammer.latitude, jammer.altitude);
        
        // 单位转换
        double P_t_linear = radar.power * 1000; // KW -> W
        double G_t_linear = ConstantValue::dBToLinear(radar.gain);
        double G_j_linear = ConstantValue::dBToLinear(jammer.gain);
        double rho_j = jammer.power / (jammer.bandwidth * 1e6); // MHz -> Hz

        // 计算目标信号在接收机处的功率（假设双程）
        double targetPowerAtReceiver = (P_t_linear * G_t_linear * G_t_linear * ConstantValue::dBToLinear(rcs.rcs_value) * pow(ConstantValue::dBToLinear(radar.wavelength), 2))
                                       / (pow(4 * ConstantValue::PI, 3) * pow(targetDistance, 4));
        
        // 计算干扰信号在接收机处的功率
        double jammerPowerAtReceiver = (rho_j * G_j_linear * G_t_linear)
                                       / (pow(4 * ConstantValue::PI, 2) * pow(jammerDistance, 2));

        totalTargetSignalPower += targetPowerAtReceiver;
        totalJammerSignalPower += jammerPowerAtReceiver;
    }
    
    double K_Jmin = ConstantValue::dBToLinear(ConstantValue::K_Jmin_dB);
    double numerator = totalTargetSignalPower;
    double denominator = K_Jmin * totalJammerSignalPower;

    // 这里需要根据新的模型推导出距离公式
    // 假设探测距离与S/J成正比，即 R_det ^ 4 正比于 S/J
    // 简化为：R^4 = C * (totalTargetSignalPower / totalJammerSignalPower)
    // 我们可以通过一个标定系数将这个比值转换为距离
    // 简化处理：将公式简化为与单机有干扰公式类似的形式，但分子分母都为累加和
    double numerator_new = (radars[0].power * 1000 * ConstantValue::dBToLinear(radars[0].gain) * rcs.rcs_value);
    double denominator_new = (4 * ConstantValue::PI * (jammer.power / (jammer.bandwidth * 1e6)) * ConstantValue::dBToLinear(jammer.gain) * ConstantValue::dBToLinear(ConstantValue::K_Jmin_dB));
    double R_J_new = pow( (numerator_new / denominator_new), 0.25);
    
    return pow(numerator / denominator, 0.25);
}

//抗干扰条件下
double FormationEvaluation::calculateDistanceWithAntiJam(const std::vector<RadarModel>& radars,
                                                const JammerModel& jammer,
                                                const TargetModel& target,
                                                const RcsData& rcs) {
    // 改进：使用空间距离进行计算，并引入抗干扰改善因子
    double totalTargetSignalPower = 0.0;
    double totalJammerSignalPower = 0.0;

    for (const auto& radar : radars) {
        // 计算雷达到目标和雷达到干扰机的距离
        double targetDistance = calculateSpatialDistance(radar.longitude, radar.latitude, radar.altitude,
                                                         target.longitude, target.latitude, target.altitude);
        double jammerDistance = calculateSpatialDistance(radar.longitude, radar.latitude, radar.altitude,
                                                         jammer.longitude, jammer.latitude, jammer.altitude);
        
        // 单位转换
        double P_t_linear = radar.power * 1000; // KW -> W
        double G_t_linear = ConstantValue::dBToLinear(radar.gain);
        double G_j_linear = ConstantValue::dBToLinear(jammer.gain);
        double rho_j = jammer.power / (jammer.bandwidth * 1e6); // MHz -> Hz

        // 计算目标信号在接收机处的功率（假设双程）
        double targetPowerAtReceiver = (P_t_linear * G_t_linear * G_t_linear * ConstantValue::dBToLinear(rcs.rcs_value) * pow(ConstantValue::dBToLinear(radar.wavelength), 2))
                                       / (pow(4 * ConstantValue::PI, 3) * pow(targetDistance, 4));
        
        // 计算干扰信号在接收机处的功率
        double jammerPowerAtReceiver = (rho_j * G_j_linear * G_t_linear)
                                       / (pow(4 * ConstantValue::PI, 2) * pow(jammerDistance, 2));

        totalTargetSignalPower += targetPowerAtReceiver;
        totalJammerSignalPower += jammerPowerAtReceiver;
    }
    
    // 引入抗干扰改善因子F_I
    double F_I = ConstantValue::dBToLinear(ConstantValue::F_I); 
    totalJammerSignalPower /= F_I;

    double K_Jmin = ConstantValue::dBToLinear(ConstantValue::K_Jmin_dB);
    double numerator = totalTargetSignalPower;
    double denominator = K_Jmin * totalJammerSignalPower;

    return pow(numerator / denominator, 0.25);
}