#pragma once
#include <QDialog>
#include <QListWidget>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton> 
#include <QStackedWidget>
#include "RadarModelDAO.h"   // 包含RadarModel结构体
#include "JammerModelDAO.h"  // 包含JammerModel结构体
#include "TargetModelDAO.h"  // 包含TargetModel结构体
#include "RcsDataDAO.h"      // 包含RcsData结构体

class ModelSelectionDialog : public QDialog {
    Q_OBJECT
public:
    explicit ModelSelectionDialog(QWidget *parent = nullptr, bool isTarget = false);
    
    void setModels(const std::vector<RadarModel>& models);
    void setModels(const std::vector<JammerModel>& models);
    void setModels(const std::vector<TargetModel>& models, bool showRcs = false);
    
signals:
    void modelSelected(const QVariant& model);
    void rcsSelected(const RcsData& rcs);

private slots:
    void onModelSelected(QListWidgetItem *item);
    void onRcsSelected(QListWidgetItem *item);
    void onAccept();
    void onReturn();  // 添加返回处理函数声明

private:
    QListWidget *modelList;
    QListWidget *rcsList;
    QStackedWidget *stackedWidget;
    QDialogButtonBox *buttonBox;
    QPushButton* returnButton;  // 添加返回按钮声明
    bool isTargetModel;
    TargetModel selectedTargetModel;  // 添加成员变量存储选中的目标模型
    
    std::vector<RadarModel> radarModels;
    std::vector<JammerModel> jammerModels;
    std::vector<TargetModel> targetModels;
    std::vector<RcsData> currentRcsData;
};