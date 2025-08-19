//存储单机评估公式常量
#ifndef CONSTANTVALUE_H
#define CONSTANTVALUE_H
#include <cmath>

class ConstantValue {
public:
    // 系统损耗因子（线性值）
    static constexpr double L = 10.0;
    
    // 接收机最小可检测信号功率 (W)
    static constexpr double S_min = 1e-12;
    
    // 雷达最小可检测信干比 (dB)
    static constexpr double K_Jmin_dB = 10.0;
    
    // 抗干扰改善因子 (dB)
    static constexpr double F_I_dB = 10.0;
    
    // 信号持续时间 (s)
    static constexpr double T0 = 1.0;
    
    // 极化失配损失系数
    static constexpr double r_J = 1.0;
    
    // 天线增益比（自卫干扰）
    static constexpr double g = 1.0;
    
    // 将dB转换为线性值
    static double dBToLinear(double dB) {
        return pow(10.0, dB / 10.0);
    }
    // 新增编队评估常量
    static constexpr double k_boltzmann = 1.38e-23; // 玻尔兹曼常数 (J/K)
    static constexpr double F_n = 2.0;              // 接收机噪声系数（线性值，约3dB）
    static constexpr double gamma_j = 0.5;          // 干扰极化系数
    static constexpr double K_j = 12.0;             // 压制系数
};

#endif // CONSTANTVALUE_H