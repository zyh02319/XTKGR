-- 雷达探测模型表 
CREATE TABLE radar_model (
    id INT PRIMARY KEY AUTO_INCREMENT COMMENT '模型ID',
    name VARCHAR(255) NOT NULL COMMENT '模型名称',
    wavelength DECIMAL(8,6) NOT NULL COMMENT '波长(m)',
    power DECIMAL(10,2) NOT NULL COMMENT '发射功率(KW)',
    bandwidth DECIMAL(10,2) NOT NULL COMMENT '信号带宽(MHz)',
    gain DECIMAL(6,2) NOT NULL COMMENT '天线增益(dB)',
    loss_factor DECIMAL(8,2) NOT NULL COMMENT '系统损耗因子',
    longitude DECIMAL(9,6) NOT NULL COMMENT '经度',
    latitude DECIMAL(8,6) NOT NULL COMMENT '纬度',
    altitude DECIMAL(10,2) NOT NULL COMMENT '高度(m)',
    position POINT NOT NULL COMMENT '空间位置',
    created_at TIMESTAMP(6) DEFAULT CURRENT_TIMESTAMP(6) COMMENT '创建时间(微秒精度)',
    SPATIAL INDEX(position)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='雷达探测模型';

-- 空间索引优化地理查询
CREATE INDEX idx_radar_location ON radar_model (longitude, latitude);