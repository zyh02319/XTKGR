#pragma once
#include <QMainWindow>

class QTabWidget;
class ModelManagerView;
class DetectionPerformanceView;
class RealtimeSimulationView;
class PostMissionEvaluationView;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QTabWidget *tabWidget;
    ModelManagerView *modelManagerView;
    DetectionPerformanceView *detectionPerformanceView;
    RealtimeSimulationView *realtimeSimulationView;
    PostMissionEvaluationView *postMissionEvaluationView;
};
