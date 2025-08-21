// FormationEvaluation.cpp
#include "FormationEvaluation.h"

//无干扰条件下
double FormationEvaluation::calculateWithoutJam(const std::vector<RadarModel>& radars,
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

//干扰条件下
double FormationEvaluation::calculateWithJam(const std::vector<RadarModel>& radars,
                                                const JammerModel& jammer,
                                                const RcsData& rcs) {
    // 多站雷达基线长度满足L≥λR/D时，目标回波互不相关，干扰信号强相关
    // 选取主站（如第1部雷达）作为基准
    const RadarModel& mainRadar = radars[0];
    
    // 单位转换：KW -> W
    double P_t_main = mainRadar.power * 1000;
    
    // dB转线性值（文档公式（2.18）、（2.20）：天线增益影响回波幅度）
    double G_t_main = ConstantValue::dBToLinear(mainRadar.gain);
    double G_j = ConstantValue::dBToLinear(jammer.gain);
    double K_Jmin = ConstantValue::dBToLinear(ConstantValue::K_Jmin_dB);

    // 目标RCS
    double sigma = rcs.rcs_value;

    // 多站目标信号叠加增益
    double targetGain = 1.0; // 主站基础增益
    for (size_t i = 1; i < radars.size(); ++i) {
        double P_t_sub = radars[i].power * 1000;
        double G_t_sub = ConstantValue::dBToLinear(radars[i].gain);
        // 子站对目标信号的贡献（加权叠加，基于公式（2.18）的增益关系）
        targetGain += (P_t_sub * G_t_sub) / (P_t_main * G_t_main) * ConstantValue::sub_weight; // 子站权重系数
    }
   
    // 多站干扰信号叠加增益
    double jammerGain = radars.size();

    // 干扰机单位频带功率
    double rho_j = jammer.power / (jammer.bandwidth * 1e6); // MHz -> Hz

    // 分子：noise_temperature为系统噪声温度,propagation_constant为传播常数
    double numerator = P_t_main * G_t_main * sigma * ConstantValue::noise_temperature *ConstantValue::propagation_constant * targetGain;
    // 分母：interference_path_loss为干扰路径损耗，K_Jmin为雷达最小可检测信干比
    double denominator = 4 * ConstantValue::PI * rho_j * G_j * ConstantValue::interference_path_loss * K_Jmin * jammerGain;

    // 四次方根计算
    return pow(numerator / denominator, 0.25);
}
//抗干扰条件下
double FormationEvaluation::calculateWithAntiJam(const std::vector<RadarModel>& radars,
                                                const JammerModel& jammer,
                                                const RcsData& rcs) {
    const RadarModel& mainRadar = radars[0];
    
    // 单位转换：KW -> W
    double P_t_main = mainRadar.power * 1000;
    
    // dB转线性值（文档公式2.18、2.20）
    double G_t_main = ConstantValue::dBToLinear(mainRadar.gain);
    double G_j = ConstantValue::dBToLinear(jammer.gain);
    double K_Jmin = ConstantValue::dBToLinear(ConstantValue::K_Jmin_dB);

    // 目标RCS
    double sigma = rcs.rcs_value;

    // 多站目标信号叠加增益（文档2.3.1节）
    double targetGain = 1.0;
    for (size_t i = 1; i < radars.size(); ++i) {
        double P_t_sub = radars[i].power * 1000;
        double G_t_sub = ConstantValue::dBToLinear(radars[i].gain);
        targetGain += (P_t_sub * G_t_sub) / (P_t_main * G_t_main) * ConstantValue::sub_weight;
    }
   
    // 抗干扰后干扰叠加增益（取原增益的10%，文档3.2节仿真）
    double jammerGain_residual = radars.size() * ConstantValue::jammerGain_residual;

    // 干扰机单位频带功率
    double rho_j = jammer.power / (jammer.bandwidth * 1e6);

    // 抗干扰改善因子
    double F_I = pow(10.0, ConstantValue::F_I / 10.0); 

    // 分子：引入抗干扰改善因子F_I
    double numerator = P_t_main * G_t_main * sigma 
                     * ConstantValue::noise_temperature 
                     * ConstantValue::propagation_constant 
                     * targetGain 
                     * F_I;
    // 分母：使用干扰残余增益
    double denominator = 4 * ConstantValue::PI 
                       * rho_j 
                       * G_j 
                       * ConstantValue::interference_path_loss 
                       * K_Jmin 
                       * jammerGain_residual;

    // 四次方根计算
    return pow(numerator / denominator, 0.25);
}

