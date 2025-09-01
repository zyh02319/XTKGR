#pragma once
#include <QWidget>

class QPushButton;
class QLabel;
class QProgressBar;
class QTableWidget;

class RealtimeSimulationView : public QWidget {

public:
    explicit RealtimeSimulationView(QWidget *parent = nullptr);

private:
    void setupUI();
};