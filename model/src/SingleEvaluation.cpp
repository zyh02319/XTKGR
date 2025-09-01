#include "SingleEvaluation.h"
#include <cmath>

// 无干扰计算函数
double SingleEvaluation::calculateDistanceWithoutJam(const RadarModel& radar, const RcsData& rcs) {
    // 公式: R_max^4 = (P_t * G_t^2 * λ^2 * σ) / [(4π)^3 * L * S_min]
    
    // 单位转换: KW -> W
    double P_t = radar.power * 1000; 
    
    // dB转线性值
    double G_t = ConstantValue::dBToLinear(radar.gain);
    
    double lambda = radar.wavelength;
    double sigma = rcs.rcs_value;
    
    double numerator = P_t * pow(G_t, 2) * pow(lambda, 2) * sigma;
    double denominator = pow(4 * ConstantValue::PI, 3) * ConstantValue::L * ConstantValue::S_min;
    
    return pow(numerator / denominator, 0.25);
}

// 有干扰计算函数
double SingleEvaluation::calculateDistanceWithJam(const RadarModel& radar, 
                                         const JammerModel& jammer, 
                                         const RcsData& rcs,
                                         double jammerDistance) {  // 参数改为雷达与干扰机的距离
    // 单位转换: KW -> W
    double P_t = radar.power * 1000; 
    
    // dB转线性值
    double G_t = ConstantValue::dBToLinear(radar.gain);
    double G_j = ConstantValue::dBToLinear(jammer.gain);
    double K_Jmin = ConstantValue::dBToLinear(ConstantValue::K_Jmin_dB);
    
    double sigma = rcs.rcs_value;
    
    // 干扰机单位频带功率 ρ_J = P_J / B_J (W/Hz)
    double rho_j = jammer.power / (jammer.bandwidth * 1e6); // MHz -> Hz
    
    // 使用雷达与干扰机的距离 R_j
    double numerator = P_t * ConstantValue::T0 * G_t * sigma * ConstantValue::g * (jammerDistance * jammerDistance);
    double denominator = 4 * ConstantValue::PI * rho_j * G_j * ConstantValue::r_J * K_Jmin;
    
    // 四次方根计算
    return pow(numerator / denominator, 0.25);
}

// 抗干扰计算函数
double SingleEvaluation::calculateDistanceWithAntiJam(const RadarModel& radar, 
                                             const JammerModel& jammer, 
                                             const RcsData& rcs, 
                                             double jammerDistance) {  // 参数改为雷达与干扰机的距离
    // 先计算有干扰距离
    double R_J0 = calculateDistanceWithJam(radar, jammer, rcs, jammerDistance);
    double F_I = ConstantValue::dBToLinear(ConstantValue::F_I_dB);
    
    // 保持四次方关系
    return R_J0 * pow(F_I, 0.25);
}