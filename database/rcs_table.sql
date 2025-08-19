-- RCS表
CREATE TABLE rcs_table (
    target_model_id INT NOT NULL COMMENT '目标模型ID',
    azimuth DECIMAL(5,2) NOT NULL COMMENT '方位角(0-360度)',
    elevation DECIMAL(5,2) NOT NULL COMMENT '俯仰角(-90-90度)',
    rcs_value DECIMAL(10,4) NOT NULL COMMENT 'RCS值(平方米)',
    PRIMARY KEY (target_model_id, azimuth, elevation),
    FOREIGN KEY (target_model_id) 
        REFERENCES target_model(id)
        ON DELETE CASCADE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='目标RCS数据表';