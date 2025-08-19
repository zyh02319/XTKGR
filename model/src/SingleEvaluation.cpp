#include "SingleEvaluation.h"
#include <cmath>

constexpr double PI = 3.14159265358979323846;

double SingleEvaluation::calculateWithoutJam(const RadarModel& radar, const RcsData& rcs) {
    // 公式: R_max^4 = (P_t * G_t^2 * λ^2 * σ) / [(4π)^3 * L * S_min]
    
    // 单位转换: KW -> W
    double P_t = radar.power * 1000; 
    
    // dB转线性值
    double G_t = ConstantValue::dBToLinear(radar.gain);
    
    double lambda = radar.wavelength;
    double sigma = rcs.rcs_value;
    
    double numerator = P_t * pow(G_t, 2) * pow(lambda, 2) * sigma;
    double denominator = pow(4 * PI, 3) * ConstantValue::L * ConstantValue::S_min;
    
    return pow(numerator / denominator, 0.25);
}

// double SingleEvaluation::calculateWithJam(const RadarModel& radar, const JammerModel& jammer, const RcsData& rcs) {
//     // 公式: R_J0^2 = (P_t * T0 * G_t * σ * g) / (4 * π * ρ_J * G_J * r_J * K_Jmin)
    
//     // 单位转换: KW -> W
//     double P_t = radar.power * 1000; 
    
//     // dB转线性值
//     double G_t = ConstantValue::dBToLinear(radar.gain);
//     double G_j = ConstantValue::dBToLinear(jammer.gain);
//     double K_Jmin = ConstantValue::dBToLinear(ConstantValue::K_Jmin_dB);
    
//     double sigma = rcs.rcs_value;
    
//     // 干扰机单位频带功率 ρ_J = P_J / B_J (W/Hz)
//     double rho_j = jammer.power / (jammer.bandwidth * 1e6); // MHz -> Hz
    
//     double numerator = P_t * ConstantValue::T0 * G_t * sigma * ConstantValue::g;
//     double denominator = 4 * PI * rho_j * G_j * ConstantValue::r_J * K_Jmin;
    
//     // return sqrt(numerator / denominator);
//     return sqrt(sqrt(numerator / denominator));
// }
// 有干扰计算 - 添加距离参数
// double SingleEvaluation::calculateWithJam(const RadarModel& radar, const JammerModel& jammer, const RcsData& rcs, double distance) {
//     // 公式: R_J0^2 = (P_t * T0 * G_t * σ * g * R_J^2) / (4 * π * ρ_J * G_J * r_J * K_Jmin)
    
//     // 单位转换: KW -> W
//     double P_t = radar.power * 1000; 
    
//     // dB转线性值
//     double G_t = ConstantValue::dBToLinear(radar.gain);
//     double G_j = ConstantValue::dBToLinear(jammer.gain);
//     double K_Jmin = ConstantValue::dBToLinear(ConstantValue::K_Jmin_dB);
    
//     double sigma = rcs.rcs_value;
    
//     // 干扰机单位频带功率 ρ_J = P_J / B_J (W/Hz)
//     double rho_j = jammer.power / (jammer.bandwidth * 1e6); // MHz -> Hz
    
//     // 添加距离参数 R_J^2
//     double numerator = P_t * ConstantValue::T0 * G_t * sigma * ConstantValue::g * (distance * distance);
//     double denominator = 4 * PI * rho_j * G_j * ConstantValue::r_J * K_Jmin;
    
//     return sqrt(numerator / denominator);
// }
// 有干扰计算函数
double SingleEvaluation::calculateWithJam(const RadarModel& radar, 
                                         const JammerModel& jammer, 
                                         const RcsData& rcs,
                                         double distance) 
{
    // 单位转换: KW -> W
    double P_t = radar.power * 1000; 
    
    // dB转线性值
    double G_t = ConstantValue::dBToLinear(radar.gain);
    double G_j = ConstantValue::dBToLinear(jammer.gain);
    double K_Jmin = ConstantValue::dBToLinear(ConstantValue::K_Jmin_dB);
    
    double sigma = rcs.rcs_value;
    
    // 干扰机单位频带功率 ρ_J = P_J / B_J (W/Hz)
    double rho_j = jammer.power / (jammer.bandwidth * 1e6); // MHz -> Hz
    
    // 修改为四次方根计算
    double numerator = P_t * ConstantValue::T0 * G_t * sigma * ConstantValue::g * (distance * distance);
    double denominator = 4 * PI * rho_j * G_j * ConstantValue::r_J * K_Jmin;
    
    // 四次方根计算
    return pow(numerator / denominator, 0.25);
}

// 抗干扰计算函数
double SingleEvaluation::calculateWithAntiJam(const RadarModel& radar, 
                                             const JammerModel& jammer, 
                                             const RcsData& rcs, 
                                             double distance) 
{
    // 先计算有干扰距离
    double R_J0 = calculateWithJam(radar, jammer, rcs, distance);
    double F_I = ConstantValue::dBToLinear(ConstantValue::F_I_dB);
    
    // 保持四次方关系
    return R_J0 * pow(F_I, 0.25);
}
// double SingleEvaluation::calculateWithAntiJam(const RadarModel& radar, const JammerModel& jammer, const RcsData& rcs) {
//     // 公式: R_J0_anti = R_J0 * F_I^(1/4)
//     double R_J0 = calculateWithJam(radar, jammer, rcs);
//     double F_I = ConstantValue::dBToLinear(ConstantValue::F_I_dB);
//     return R_J0 * pow(F_I, 0.25);
// }

// 抗干扰计算 - 添加距离参数
// double SingleEvaluation::calculateWithAntiJam(const RadarModel& radar, const JammerModel& jammer, const RcsData& rcs, double distance) {
//     // 公式: R_J0_anti = R_J0 * F_I^(1/4)
//     double R_J0 = calculateWithJam(radar, jammer, rcs, distance);
//     double F_I = ConstantValue::dBToLinear(ConstantValue::F_I_dB);
//     return R_J0 * pow(F_I, 0.25);
// }