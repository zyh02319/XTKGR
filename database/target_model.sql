-- 目标模型表
CREATE TABLE target_model (
    id INT PRIMARY KEY AUTO_INCREMENT COMMENT '模型ID',
    name VARCHAR(255) NOT NULL COMMENT '模型名称',
    target_type ENUM('空中', '地面', '海上', '太空') NOT NULL DEFAULT '空中' COMMENT '目标类型',
    longitude DECIMAL(9,6) NOT NULL COMMENT '经度',
    latitude DECIMAL(8,6) NOT NULL COMMENT '纬度',
    altitude DECIMAL(10,2) NOT NULL COMMENT '高度(m)',
    position POINT NOT NULL COMMENT '空间位置',
    created_at TIMESTAMP(6) DEFAULT CURRENT_TIMESTAMP(6) COMMENT '创建时间(微秒精度)',
    SPATIAL INDEX(position)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='目标模型';

-- 空间索引优化地理查询
CREATE INDEX idx_target_location ON target_model (longitude, latitude);

ALTER TABLE target_model 
ADD COLUMN heading DECIMAL(5,2) COMMENT '航向(0-360度)' AFTER position,
ADD COLUMN speed DECIMAL(8,2) COMMENT '飞行速度(km/h)' AFTER heading;