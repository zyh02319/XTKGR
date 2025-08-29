# 协同抗干扰仿真分析系统

## 项目简介
本项目用于实现基于MVC架构的协同抗干扰仿真分析系统，支持多种干扰/抗干扰模型、雷达探测模型、目标模型的管理与仿真评估。系统采用C++开发，QT实现可视化界面，MySQL进行数据管理，支持在Ubuntu 18.04下编译运行。

## 主要功能
- 干扰机、探测、目标、抗干扰模型的增删改查
- 任务前/实时/任务后仿真评估
- 单机与编队评估
- 支持真实数据导入与对比分析
- 评估结果图表与列表展示

## 目录结构
- model/        各类模型实现
- controller/   控制器实现
- view/         GTK界面实现
- data/         数据库相关
- main.cpp      程序入口
- CMakeLists.txt 构建配置

## 依赖
- C++11及以上
- GTK+3
- MySQL客户端库（libmysqlclient-dev）
- CMake
- g++

## 如果没有环境需要运行以下代码
安装 QtCharts 开发包
在 Ubuntu / Debian 下直接执行：
```bash
sudo apt-get update
sudo apt-get install libqt5charts5-dev
```
安装完成后会在 /usr/lib/x86_64-linux-gnu/cmake/Qt5Charts/Qt5ChartsConfig.cmake 生成配置文件，CMake 就能找到。

执行：
```bash
ls /usr/lib/x86_64-linux-gnu/cmake/Qt5Charts
```
如果里面有 Qt5ChartsConfig.cmake，那说明安装好了。
## 编译与运行
```bash
sudo apt update
sudo apt install build-essential cmake libgtk-3-dev libmysqlclient-dev
cd KGR
mkdir build && cd build
cmake ..
make
./KGR
```

## 使用说明

## git创建个人分支
```bash
git checkout -b dev
```
## 
例：
```bash
git checkout -b yz_dev
```

## git上传代码（执行以下命令前将build文件夹下的内容全部删除）
```bash
git add .
git commit -m ''
git push -u origin dev
```
## 
例：
```bash
git add .
git commit -m '新增地图'
git push -u origin yz_dev
```
## 如果同时修改代码，先解决冲突后再上传
```bash
git fetch
git merge origin/main

打开冲突代码文件解决冲突

git add .
git commit -m ''
git push -u origin dev
```

## 在github上提Pull Request合并到main分支

## git拉取代码
```bash
git fetch
git merge origin/main
```