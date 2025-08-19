#include "../MainWindow.h"
#include <QTabWidget>
#include "ModelManagerView.h"
#include "DetectionPerformanceView.h"
#include "RealtimeSimulationView.h"
#include "PostMissionEvaluationView.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    tabWidget = new QTabWidget(this);
    modelManagerView = new ModelManagerView(this);
    detectionPerformanceView = new DetectionPerformanceView(this);
    realtimeSimulationView = new RealtimeSimulationView(this);
    postMissionEvaluationView = new PostMissionEvaluationView(this);

    tabWidget->addTab(modelManagerView, "模型管理");
    tabWidget->addTab(detectionPerformanceView, "探测效能计算");
    tabWidget->addTab(realtimeSimulationView, "实时仿真评估");
    tabWidget->addTab(postMissionEvaluationView, "任务后仿真评估");

    setCentralWidget(tabWidget);
    setWindowTitle("协同抗干扰仿真分析系统");
    resize(1000, 700);
}

MainWindow::~MainWindow() {} 