#ifndef CONSTANTVALUE_H
#define CONSTANTVALUE_H
#include <cmath>

class ConstantValue {
public:
    static constexpr double PI = 3.14159265358979323846;
    // 系统损耗因子（线性值）
    static constexpr double L = 10.0;
    
    // 接收机最小可检测信号功率 (W)
    static constexpr double S_min = 1e-12;
    
    // 雷达最小可检测信干比 (dB)
    static constexpr double K_Jmin_dB = 10.0;
    
    // 抗干扰改善因子 (dB)
    static constexpr double F_I_dB = 10.0;
    
    // 信号持续时间 (s)
    static constexpr double T0 = 1e-3;
    
    // 极化失配损失系数
    static constexpr double r_J = 1.0;
    
    // 天线增益比（自卫干扰）
    static constexpr double g = 1.0;
    
    // 将dB转换为线性值
    static double dBToLinear(double dB) {
        return pow(10.0, dB / 10.0);
    }
    // 编队评估常量
    //子站权重系数
    static constexpr double sub_weight = 0.5;
    //系统噪声温度
    static constexpr double noise_temperature = 290.0;
    //传播常数
    static constexpr double propagation_constant = 1.0;
    //干扰路径损耗
    static constexpr double interference_path_loss = 1.0;
    //抗干扰后干扰叠加增益
    static constexpr double jammerGain_residual = 0.1;
    //抗干扰改善因子(dB)
    static constexpr double F_I = 65.0;
};

#endif // CONSTANTVALUE_H