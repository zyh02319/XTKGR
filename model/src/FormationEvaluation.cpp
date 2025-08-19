// FormationEvaluation.cpp
#include "FormationEvaluation.h"

double FormationEvaluation::evaluateChengAlgorithm(
    const RadarModel& transmitter,
    const RadarModel& receiver,
    const JammerModel* jammer,
    const RcsData& rcs,
    double baseline,
    int condition) 
{
    // 1. 转换单位
    double P_t = transmitter.power * 1000;  // kW -> W
    double lambda = transmitter.wavelength;
    double G_t = ConstantValue::dBToLinear(transmitter.gain);
    double G_r = ConstantValue::dBToLinear(receiver.gain); // 使用接收站增益
    double sigma = rcs.rcs_value;
    
    // 2. 无干扰条件
    if (condition == 0 || jammer == nullptr) {
        double numerator = P_t * G_t * G_r * pow(lambda, 2) * sigma;
        double denominator = pow(4 * M_PI, 3) * ConstantValue::L * ConstantValue::S_min;
        return pow(numerator / denominator, 0.25);  // R = [num/den]^(1/4)
    }
    
    // 3. 干扰条件
    double P_j = jammer->power;
    double G_j = ConstantValue::dBToLinear(jammer->gain);
    double B_j = jammer->bandwidth * 1e6;  // MHz -> Hz
    double B_r = transmitter.bandwidth * 1e6;  // MHz -> Hz
    
    // 4. 计算干扰等效噪声温度
    double T_J = (P_j * G_j * G_r * pow(lambda, 2)) / 
                 (pow(4 * M_PI, 2) * pow(baseline, 2) * ConstantValue::k_boltzmann * B_j);
    
    // 5. 计算信干比
    double numerator = P_t * G_t * G_r * pow(lambda, 2) * sigma;
    double denominator = pow(4 * M_PI, 3) * pow(baseline, 4) * ConstantValue::k_boltzmann * 
                         (ConstantValue::F_n + T_J) * B_r * ConstantValue::L; // 移除多余的F_n
    
    double K_Jmin = ConstantValue::dBToLinear(ConstantValue::K_Jmin_dB);
    
    // 6. 计算探测距离
    return pow(numerator / (denominator * K_Jmin), 0.25);
}


double FormationEvaluation::evaluateLiaoAlgorithm(
    const RadarModel& transmitter,
    const RadarModel& receiver,
    const JammerModel* jammer,
    const RcsData& rcs,
    double baseline,
    int condition) 
{
    // 1. 转换单位
    double P_t = transmitter.power * 1000;  // kW -> W
    double G_t = ConstantValue::dBToLinear(transmitter.gain);
    double G_r = ConstantValue::dBToLinear(receiver.gain); // 使用接收站增益
    double sigma = rcs.rcs_value;
    
    // 2. 无干扰条件
    if (condition == 0 || jammer == nullptr) {
        double numerator = P_t * G_t * G_r * pow(transmitter.wavelength, 2) * sigma;
        double denominator = pow(4 * M_PI, 3) * ConstantValue::L * ConstantValue::S_min;
        return pow(numerator / denominator, 0.25);
    }
    
    // 3. 干扰条件
    double P_j = jammer->power;
    double G_j = ConstantValue::dBToLinear(jammer->gain);
    double delta_f_j = jammer->bandwidth * 1e6;  // MHz -> Hz
    double delta_f_r = transmitter.bandwidth * 1e6;  // MHz -> Hz
    
    // 4. 计算探测距离
    double numerator = ConstantValue::K_j * P_t * G_t * sigma * delta_f_j;
    double denominator = 4 * M_PI * P_j * G_j * ConstantValue::gamma_j * delta_f_r;
    
    return sqrt(numerator / denominator);
}