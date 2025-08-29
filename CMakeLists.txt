cmake_minimum_required(VERSION 3.10)
project(KGR)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
pkg_check_modules(MYSQL REQUIRED mysqlclient)
#find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Widgets Charts REQUIRED)
include_directories(
    ${GTK3_INCLUDE_DIRS}
    ${MYSQL_INCLUDE_DIRS}
    include
    model
    controller
    view
    data
)

link_directories(${GTK3_LIBRARY_DIRS} ${MYSQL_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

# 手动列出所有源文件和头文件
add_executable(KGR
    main.cpp
    view/src/DetectionPerformanceView.cpp
    view/DetectionPerformanceView.h
    view/src/MainWindow.cpp
    view/MainWindow.h
    view/src/ModelManagerView.cpp
    view/ModelManagerView.h
    view/src/RealtimeSimulationView.cpp
    view/RealtimeSimulationView.h
    view/src/PostMissionEvaluationView.cpp
    view/PostMissionEvaluationView.h
    #新加文件
    view/src/ModelSelectionDialog.cpp
    view/ModelSelectionDialog.h
    view/DetectionPerformanceView.h
    view/src/DetectionPerformanceView.cpp
    view/JammerModelEditDialog.h
    view/JammerModelViewDialog.h
    view/src/JammerModelEditDialog.cpp
    view/src/JammerModelViewDialog.cpp
    view/RadarModelViewDialog.h
    view/RadarModelEditDialog.h
    view/src/RadarModelEditDialog.cpp
    view/src/RadarModelViewDialog.cpp
    view/TargetModelViewDialog.h
    view/TargetModelEditDialog.h
    view/RcsEditDialog.h
    view/src/RcsEditDialog.cpp
    view/src/TargetModelEditDialog.cpp
    view/src/TargetModelViewDialog.cpp
    data/DBConfig.h
    data/DataManager.h
    data/src/DataManager.cpp
    controller/ModelManageController.h
    controller/src/ModelManageController.cpp
    controller/src/SingleEvaluationController.cpp
    controller/SingleEvaluationController.h
    model/ConstantValue.h
    model/SingleEvaluation.h
    model/src/SingleEvaluation.cpp
    model/JammerModelDAO.h
    model/RadarModelDAO.h
    model/RcsDataDAO.h
    model/TargetModelDAO.h
    model/TargetModelWithRcs.h
    model/src/JammerModelDAO.cpp
    model/src/RadarModelDAO.cpp
    model/src/RcsDataDAO.cpp
    model/src/TargetModelDAO.cpp
    model/src/TargetModelWithRcs.cpp
    #编队评估
    model/FormationEvaluation.h
    model/src/FormationEvaluation.cpp
    controller/FormationEvaluationController.h
    controller/src/FormationEvaluationController.cpp
    # 其他 cpp/h 文件
)


#target_link_libraries(KGR Qt5::Widgets ${GTK3_LIBRARIES} ${MYSQL_LIBRARIES})
target_link_libraries(KGR Qt5::Widgets Qt5::Charts ${GTK3_LIBRARIES} ${MYSQL_LIBRARIES})
