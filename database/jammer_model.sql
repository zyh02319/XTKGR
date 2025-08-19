-- 干扰机模型表
CREATE TABLE jammer_model (
    id INT PRIMARY KEY AUTO_INCREMENT COMMENT '模型ID',
    name VARCHAR(255) NOT NULL COMMENT '模型名称',
    jamming_type ENUM('欺骗式', '压制式', '复合式', '其他') NOT NULL COMMENT '干扰样式',
    power DECIMAL(10,2) NOT NULL COMMENT '干扰功率(W)',
    bandwidth DECIMAL(10,2) NOT NULL COMMENT '干扰带宽(MHz)',
    gain DECIMAL(6,2) NOT NULL COMMENT '干扰增益(dB)',
    longitude DECIMAL(9,6) NOT NULL COMMENT '经度',
    latitude DECIMAL(8,6) NOT NULL COMMENT '纬度',
    altitude DECIMAL(10,2) NOT NULL COMMENT '高度(m)',
    position POINT NOT NULL COMMENT '空间位置',
    created_at TIMESTAMP(6) DEFAULT CURRENT_TIMESTAMP(6) COMMENT '创建时间(微秒精度)',
    SPATIAL INDEX(position)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='干扰机模型';

-- 空间索引优化地理查询
CREATE INDEX idx_jammer_location ON jammer_model (longitude, latitude);