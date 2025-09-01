#include "DetectionPerformanceView.h"
#include "ModelSelectionDialog.h"
#include "SingleEvaluationController.h"
#include "FormationEvaluationController.h"
#include <QMessageBox>
#include <QInputDialog>
#include <iostream>
#include <cmath>
#include <QGridLayout>
#include <QGroupBox>
#include <QStringList>

DetectionPerformanceView::DetectionPerformanceView(QWidget *parent)
    : QWidget(parent), 
      radarDialog(nullptr),
      jammerDialog(nullptr), targetDialog(nullptr),
      currentRadar(nullptr), currentJammer(nullptr), currentTarget(nullptr),
      currentFormationJammer(nullptr), currentFormationTarget(nullptr)
{
    setupUI();
}


DetectionPerformanceView::~DetectionPerformanceView() {
    delete radarDialog;
    delete jammerDialog;
    delete targetDialog;
    delete radarDialogForFormationRadar;
    delete jammerDialogForFormation;
    delete targetDialogForFormationTarget;
    delete currentRadar;
    delete currentJammer;
    delete currentTarget;
    
    for (RadarModel* radarPtr : currentFormationRadars) {
        delete radarPtr;
    }
    currentFormationRadars.clear();
    delete currentFormationJammer;
    delete currentFormationTarget;
    
}

void DetectionPerformanceView::setupUI() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // 创建标签页
    tabWidget = new QTabWidget(this);
    singleEvaluationTab = new QWidget();
    formationEvaluationTab = new QWidget(); // 编队评估标签页
    
    // 设置单机评估页面
    setupSingleEvaluationUI();
    
    // 设置编队评估页面
    setupFormationUI();
    
    // 添加标签页
    tabWidget->addTab(singleEvaluationTab, "单机评估");
    tabWidget->addTab(formationEvaluationTab, "编队评估");
    
    mainLayout->addWidget(tabWidget);
}
//单机评估页面
void DetectionPerformanceView::setupSingleEvaluationUI() {
    QVBoxLayout *singleLayout = new QVBoxLayout(singleEvaluationTab);
    
    // 条件选择
    QGroupBox *conditionGroup = new QGroupBox("评估场景", this);
    conditionGroup->setMaximumHeight(100);
    QHBoxLayout *conditionLayout = new QHBoxLayout;
    conditionComboBox = new QComboBox(this);
    conditionComboBox->addItem("无干扰");
    conditionComboBox->addItem("有干扰");
    conditionComboBox->addItem("抗干扰");
    conditionLayout->addWidget(new QLabel("干扰情况:"));
    conditionLayout->addWidget(conditionComboBox);
    conditionGroup->setLayout(conditionLayout);
    
    // 模型选择
    QGroupBox *modelGroup = new QGroupBox("模型选择", this);
    QGridLayout *modelLayout = new QGridLayout;
    
    selectRadarButton = new QPushButton("选择探测模型", this);
    selectJammerButton = new QPushButton("选择干扰模型", this);
    selectTargetButton = new QPushButton("选择目标模型", this);
    evaluateButton = new QPushButton("评估", this);
    
    radarLabel = new QLabel("未选择", this);
    jammerLabel = new QLabel("未选择", this);
    targetLabel = new QLabel("未选择", this);
    
    
    QPushButton *radarDetailButton = new QPushButton("查看", this);
    QPushButton *jammerDetailButton = new QPushButton("查看", this);
    QPushButton *targetDetailButton = new QPushButton("查看", this);
    
    modelLayout->addWidget(new QLabel("探测模型:"), 0, 0);
    modelLayout->addWidget(radarLabel, 0, 1);
    modelLayout->addWidget(selectRadarButton, 0, 2);
    modelLayout->addWidget(radarDetailButton, 0, 3);
    
    modelLayout->addWidget(new QLabel("干扰模型:"), 1, 0);
    modelLayout->addWidget(jammerLabel, 1, 1);
    modelLayout->addWidget(selectJammerButton, 1, 2);
    modelLayout->addWidget(jammerDetailButton, 1, 3);
    
    modelLayout->addWidget(new QLabel("目标模型:"), 2, 0);
    modelLayout->addWidget(targetLabel, 2, 1);
    modelLayout->addWidget(selectTargetButton, 2, 2);
    modelLayout->addWidget(targetDetailButton, 2, 3);
    
    modelLayout->addWidget(evaluateButton, 3, 0, 1, 5);
    modelGroup->setLayout(modelLayout);
    
    // 结果展示
    QGroupBox *resultGroup = new QGroupBox("评估结果", this);
    QGridLayout *resultLayout = new QGridLayout;

    // 探测距离
    QLabel *distanceLabel = new QLabel("探测距离:", this);
    distanceValue = new QLabel("-- m", this);
    QFont boldFont = distanceValue->font();
    boldFont.setBold(true);
    distanceValue->setFont(boldFont);
    distanceValue->setObjectName("distanceValue"); // 设置对象名方便后续更新

    // 目标航迹连续性
    QLabel *trackLabel = new QLabel("目标航迹连续性:", this);
    trackValue = new QLabel("--", this);
    trackValue->setFont(boldFont);
    trackValue->setObjectName("trackValue");

    // 探测中断原因
    QLabel *reasonLabel = new QLabel("探测中断/未探测到目标原因:", this);
    reasonValue = new QLabel("--", this);
    reasonValue->setObjectName("reasonValue"); 

    // 布局排列
    resultLayout->addWidget(distanceLabel, 0, 0);
    resultLayout->addWidget(distanceValue, 0, 1);
    resultLayout->addWidget(trackLabel, 1, 0);
    resultLayout->addWidget(trackValue, 1, 1);
    resultLayout->addWidget(reasonLabel, 2, 0);
    resultLayout->addWidget(reasonValue, 2, 1);

    // 设置列宽比例
    resultLayout->setColumnStretch(0, 1);
    resultLayout->setColumnStretch(1, 3);

    resultGroup->setLayout(resultLayout);
    
    // 添加到单机评估页
    singleLayout->addWidget(conditionGroup);
    singleLayout->addWidget(modelGroup);
    singleLayout->addWidget(resultGroup);
    
    // 连接信号槽
    connect(conditionComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &DetectionPerformanceView::onConditionChanged);
    connect(selectRadarButton, &QPushButton::clicked, this, &DetectionPerformanceView::onSelectRadar);
    connect(selectJammerButton, &QPushButton::clicked, this, &DetectionPerformanceView::onSelectJammer);
    connect(selectTargetButton, &QPushButton::clicked, this, &DetectionPerformanceView::onSelectTarget);
    connect(evaluateButton, &QPushButton::clicked, this, &DetectionPerformanceView::onEvaluate);
    connect(radarDetailButton, &QPushButton::clicked, this, &DetectionPerformanceView::showRadarDetails);
    connect(jammerDetailButton, &QPushButton::clicked, this, &DetectionPerformanceView::showJammerDetails);
    connect(targetDetailButton, &QPushButton::clicked, this, &DetectionPerformanceView::showTargetDetails);
    
    // 初始化状态
    onConditionChanged(0);
}
//编队评估页面
void DetectionPerformanceView::setupFormationUI() {
    QVBoxLayout *formationLayout = new QVBoxLayout(formationEvaluationTab);
    
    // 条件选择
    QGroupBox *conditionGroup = new QGroupBox("评估场景", this);
    conditionGroup->setMaximumHeight(100);
    QHBoxLayout *conditionLayout = new QHBoxLayout;
    formationConditionComboBox = new QComboBox(this);
    formationConditionComboBox->addItem("无干扰");
    formationConditionComboBox->addItem("有干扰");
    formationConditionComboBox->addItem("抗干扰");
    conditionLayout->addWidget(new QLabel("干扰情况:"));
    conditionLayout->addWidget(formationConditionComboBox);
    conditionGroup->setLayout(conditionLayout);
    
    // 模型选择
    QGroupBox *modelGroup = new QGroupBox("模型选择", this);
    QGridLayout *modelLayout = new QGridLayout;
    
    selectFormationRadarButton = new QPushButton("选择探测模型", this);
    addFormationRadarButton = new QPushButton("增加", this);
    deleteFormationRadarButton = new QPushButton("删除", this);
    selectFormationJammerButton = new QPushButton("选择干扰模型", this);
    selectFormationTargetButton = new QPushButton("选择目标模型", this);
    formationEvaluateButton = new QPushButton("评估", this);
    
    formationRadarLabel = new QLabel("未选择", this);
    formationJammerLabel = new QLabel("未选择", this);
    formationTargetLabel = new QLabel("未选择", this);
    
    
    QPushButton *formationRadarDetailButton = new QPushButton("查看", this);
    QPushButton *formationJammerDetailButton = new QPushButton("查看", this);
    QPushButton *formationTargetDetailButton = new QPushButton("查看", this);
    
    modelLayout->addWidget(new QLabel("探测模型:"), 0, 0);
    modelLayout->addWidget(formationRadarLabel, 0, 1);
    modelLayout->addWidget(selectFormationRadarButton, 0, 2);
    modelLayout->addWidget(formationRadarDetailButton, 0, 3);
    modelLayout->addWidget(addFormationRadarButton, 0, 4);
    modelLayout->addWidget(deleteFormationRadarButton, 0, 5);
    
    modelLayout->addWidget(new QLabel("干扰模型:"), 2, 0);
    modelLayout->addWidget(formationJammerLabel, 2, 1);
    modelLayout->addWidget(selectFormationJammerButton, 2, 2);
    modelLayout->addWidget(formationJammerDetailButton, 2, 3);
    
    modelLayout->addWidget(new QLabel("目标模型:"), 3, 0);
    modelLayout->addWidget(formationTargetLabel, 3, 1);
    modelLayout->addWidget(selectFormationTargetButton, 3, 2);
    modelLayout->addWidget(formationTargetDetailButton, 3, 3);
    
    modelLayout->addWidget(formationEvaluateButton, 4, 0, 1, 6);
    modelGroup->setLayout(modelLayout);
    
    // 结果展示
    QGroupBox *resultGroup = new QGroupBox("评估结果", this);
    QGridLayout *resultLayout = new QGridLayout;

    // 探测距离
    QLabel *formationDistanceLabel = new QLabel("探测距离:", this);
    formationDistanceValue = new QLabel("-- m", this);
    QFont boldFont = formationDistanceValue->font();
    boldFont.setBold(true);
    formationDistanceValue->setFont(boldFont);
    formationDistanceValue->setObjectName("formationDistanceValue"); // 设置对象名方便后续更新

    // 目标航迹连续性
    QLabel *formationTrackLabel = new QLabel("目标航迹连续性:", this);
    formationTrackValue = new QLabel("--", this);
    formationTrackValue->setFont(boldFont);
    formationTrackValue->setObjectName("formationTrackValue");

    // 探测中断原因
    QLabel *formationReasonLabel = new QLabel("探测中断/未探测到目标原因:", this);
    formationReasonValue = new QLabel("--", this);
    formationReasonValue->setObjectName("formationReasonValue"); 

    // 布局排列
    resultLayout->addWidget(formationDistanceLabel, 0, 0);
    resultLayout->addWidget(formationDistanceValue, 0, 1);
    resultLayout->addWidget(formationTrackLabel, 1, 0);
    resultLayout->addWidget(formationTrackValue, 1, 1);
    resultLayout->addWidget(formationReasonLabel, 2, 0);
    resultLayout->addWidget(formationReasonValue, 2, 1);

    // 设置列宽比例
    resultLayout->setColumnStretch(0, 1);
    resultLayout->setColumnStretch(1, 3);

    resultGroup->setLayout(resultLayout);
    
    // 添加到编队评估页
    formationLayout->addWidget(conditionGroup);
    formationLayout->addWidget(modelGroup);
    formationLayout->addWidget(resultGroup);
    
    // 连接信号槽
    connect(formationConditionComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &DetectionPerformanceView::onFormationConditionChanged);
    connect(selectFormationRadarButton, &QPushButton::clicked, 
            this, &DetectionPerformanceView::onSelectFormationRadar);
    connect(addFormationRadarButton, &QPushButton::clicked,
            this, &DetectionPerformanceView::onAddFormationRadar);
    connect(deleteFormationRadarButton, &QPushButton::clicked,
            this, &DetectionPerformanceView::onDeleteFormationRadar);
    connect(selectFormationJammerButton, &QPushButton::clicked,
            this, &DetectionPerformanceView::onSelectFormationJammer);
    connect(selectFormationTargetButton, &QPushButton::clicked, 
            this, &DetectionPerformanceView::onSelectFormationTarget);
    connect(formationEvaluateButton, &QPushButton::clicked, 
            this, &DetectionPerformanceView::onFormationEvaluate);
    connect(formationRadarDetailButton, &QPushButton::clicked, 
            this, &DetectionPerformanceView::showFormationRadarDetails);
    connect(formationJammerDetailButton, &QPushButton::clicked, 
            this, &DetectionPerformanceView::showFormationJammerDetails);
    connect(formationTargetDetailButton, &QPushButton::clicked, 
            this, &DetectionPerformanceView::showFormationTargetDetails);
    
    // 初始状态
    onFormationConditionChanged(0);
    updateFormationModelDisplay();
}
//单机评估中无干扰时禁用干扰模型选择
void DetectionPerformanceView::onConditionChanged(int index) {
    // 无干扰时禁用干扰模型选择
    selectJammerButton->setEnabled(index != 0);
    jammerLabel->setEnabled(index != 0);
    
    if (index == 0) {
        delete currentJammer;
        currentJammer = nullptr;
        jammerLabel->setText("未选择");
    }
    
    updateModelDisplay();
}
//编队评估中无干扰时禁用干扰模型选择
void DetectionPerformanceView::onFormationConditionChanged(int index) {
    selectFormationJammerButton->setEnabled(index != 0);
    formationJammerLabel->setEnabled(index != 0);
    
    if (index == 0) {
        delete currentFormationJammer;
        currentFormationJammer = nullptr;
        formationJammerLabel->setText("未选择");
    }
    
    updateFormationModelDisplay();
}
//选择单机探测模型
void DetectionPerformanceView::onSelectRadar() {
    if (!radarDialog) {
        radarDialog = new ModelSelectionDialog(this);
        radarDialog->setModels(SingleEvaluationController::getAllRadarModels());
        connect(radarDialog, &ModelSelectionDialog::modelSelected, [this](const QVariant& model) {
            delete currentRadar;
            currentRadar = new RadarModel(model.value<RadarModel>());
            updateModelDisplay();
        });
    }
    radarDialog->show();
}
//选择单机干扰模型
void DetectionPerformanceView::onSelectJammer() {
    if (!jammerDialog) {
        jammerDialog = new ModelSelectionDialog(this);
        jammerDialog->setModels(SingleEvaluationController::getAllJammerModels());
        connect(jammerDialog, &ModelSelectionDialog::modelSelected, [this](const QVariant& model) {
            delete currentJammer;
            currentJammer = new JammerModel(model.value<JammerModel>());
            updateModelDisplay();
        });
    }
    jammerDialog->show();
}
//选择单机目标模型
void DetectionPerformanceView::onSelectTarget() {
    if (!targetDialog) {
        targetDialog = new ModelSelectionDialog(this);
        targetDialog->setModels(SingleEvaluationController::getAllTargetModels(), false);
        connect(targetDialog, &ModelSelectionDialog::modelSelected, [this](const QVariant& model) {
            delete currentTarget;
            currentTarget = new TargetModel(model.value<TargetModel>());
              
            updateModelDisplay();
        });
        
    }
    targetDialog->show();
}
//选择编队探测模型
void DetectionPerformanceView::onSelectFormationRadar() {
    isAddingFormationRadar = false;
    if (!radarDialogForFormationRadar) {
        radarDialogForFormationRadar = new ModelSelectionDialog(this);
        radarDialogForFormationRadar->setModels(SingleEvaluationController::getAllRadarModels());
        connect(radarDialogForFormationRadar, &ModelSelectionDialog::modelSelected, [this](const QVariant& model) {
            RadarModel* newRadar = new RadarModel(model.value<RadarModel>());
            if (isAddingFormationRadar) {
                if (static_cast<int>(currentFormationRadars.size()) >= 4) {
                    QMessageBox::warning(this, "提示", "最多可选择四个探测模型");
                    delete newRadar;
                    return;
                }
                currentFormationRadars.push_back(newRadar);
            } else {
                if (currentFormationRadars.empty()) {
                    currentFormationRadars.push_back(newRadar);
                } else {
                    delete currentFormationRadars[0];
                    currentFormationRadars[0] = newRadar;
                }
            }
            updateFormationModelDisplay();
        });
    }
    radarDialogForFormationRadar->show();
}
//添加编队探测模型
void DetectionPerformanceView::onAddFormationRadar() {
    if (static_cast<int>(currentFormationRadars.size()) >= 4) {
        QMessageBox::warning(this, "提示", "最多可选择四个探测模型");
        return;
    }
    isAddingFormationRadar = true;
    if (!radarDialogForFormationRadar) {
        // 创建时会绑定统一的回调，回调里依据 isAddingFormationRadar 判断追加或替换
        radarDialogForFormationRadar = new ModelSelectionDialog(this);
        radarDialogForFormationRadar->setModels(SingleEvaluationController::getAllRadarModels());
        connect(radarDialogForFormationRadar, &ModelSelectionDialog::modelSelected, [this](const QVariant& model) {
            RadarModel* newRadar = new RadarModel(model.value<RadarModel>());
            if (isAddingFormationRadar) {
                if (static_cast<int>(currentFormationRadars.size()) >= 4) {
                    QMessageBox::warning(this, "提示", "最多可选择四个探测模型");
                    delete newRadar;
                    return;
                }
                currentFormationRadars.push_back(newRadar);
            } else {
                if (currentFormationRadars.empty()) {
                    currentFormationRadars.push_back(newRadar);
                } else {
                    delete currentFormationRadars[0];
                    currentFormationRadars[0] = newRadar;
                }
            }
            updateFormationModelDisplay();
        });
    }
    radarDialogForFormationRadar->show();
}

//删除编队探测模型
void DetectionPerformanceView::onDeleteFormationRadar() {
    if (currentFormationRadars.empty()) {
        QMessageBox::information(this, "提示", "当前没有选择的探测模型");
        return;
    }
    
    // 创建选择对话框
    QStringList radarNames;
    for (size_t i = 0; i < currentFormationRadars.size(); ++i) {
        RadarModel* radar = currentFormationRadars[i];
        if (radar) {
            radarNames << QString("[%1] %2").arg(i + 1).arg(QString::fromStdString(radar->name));
        }
    }
    
    bool ok;
    QString selectedRadar = QInputDialog::getItem(this, "删除探测模型", 
                                                 "请选择要删除的探测模型:", 
                                                 radarNames, 0, false, &ok);
    if (ok && !selectedRadar.isEmpty()) {
        // 解析选择的探测索引
        int index = selectedRadar.mid(1, selectedRadar.indexOf(']') - 1).toInt() - 1;
        
        if (index >= 0 && index < static_cast<int>(currentFormationRadars.size())) {
            // 删除选中的探测模型
            delete currentFormationRadars[index];
            currentFormationRadars.erase(currentFormationRadars.begin() + index);
            
            QMessageBox::information(this, "成功", "探测模型已删除");
            updateFormationModelDisplay();
        }
    }
}

//选择编队干扰模型
void DetectionPerformanceView::onSelectFormationJammer() {
    if (!jammerDialogForFormation) {
        jammerDialogForFormation = new ModelSelectionDialog(this);
        jammerDialogForFormation->setModels(SingleEvaluationController::getAllJammerModels());
        connect(jammerDialogForFormation, &ModelSelectionDialog::modelSelected, [this](const QVariant& model) {
            delete currentFormationJammer;
            currentFormationJammer = new JammerModel(model.value<JammerModel>());
            updateFormationModelDisplay();
        });
    }
    jammerDialogForFormation->show();
}
//选择编队目标模型
void DetectionPerformanceView::onSelectFormationTarget() {
    if (!targetDialogForFormationTarget){
        targetDialogForFormationTarget = new ModelSelectionDialog(this);
        targetDialogForFormationTarget->setModels(SingleEvaluationController::getAllTargetModels(), false);
        connect(targetDialogForFormationTarget, &ModelSelectionDialog::modelSelected, [this](const QVariant& model) {
            delete currentFormationTarget;
            currentFormationTarget = new TargetModel(model.value<TargetModel>());        
            updateFormationModelDisplay();
        });
    }
    targetDialogForFormationTarget->show();
}
//单机评估计算
void DetectionPerformanceView::onEvaluate() {
    // 验证输入
    if (!currentRadar) {
        QMessageBox::warning(this, "错误", "请选择探测模型");
        return;
    }
    if (conditionComboBox->currentIndex() != 0 && !currentJammer) {
        QMessageBox::warning(this, "错误", "请选择干扰模型");
        return;
    }
    if (!currentTarget) {
        QMessageBox::warning(this, "错误", "请选择目标模型");
        return;
    }
    
    // 计算探测与目标的空间距离
    double distance = calculateSpatialDistance(
        currentRadar->longitude, currentRadar->latitude, currentRadar->altitude,
        currentTarget->longitude, currentTarget->latitude, currentTarget->altitude
    );
    
    // 计算探测距离
    try {
        JammerModel defaultJammer;
        if (conditionComboBox->currentIndex() == 0) {
            defaultJammer = JammerModel();
        }
        
        // 调用单机评估控制器
        // 固定RCS=50
        RcsData fixedRcs; fixedRcs.rcs_value = 50.0; fixedRcs.azimuth = 0; fixedRcs.elevation = 0;
        double resultDistance = SingleEvaluationController::calculateDistance(
            conditionComboBox->currentIndex(),
            *currentRadar,
            (conditionComboBox->currentIndex() == 0) ? defaultJammer : *currentJammer,
            fixedRcs,
            distance
        );

        //更新探测距离
        if (distanceValue) {
            // 显示计算结果，保留2位小数
            distanceValue->setText(QString("%1 米").arg(resultDistance, 0, 'f', 2));
        } else {
            // 容错处理：如果未找到控件，显示错误信息
            QMessageBox::warning(this, "错误", "评估结果区域未初始化");
        }
        
        // 更新目标航迹连续性
        if (trackValue) {
            // 根据干扰情况设置不同的航迹连续性值
            double trackContinuity = 95.0; // 默认值
            if (conditionComboBox->currentIndex() == 1) { // 有干扰
                trackContinuity = 85.0;
            } else if (conditionComboBox->currentIndex() == 2) { // 抗干扰
                trackContinuity = 92.0;
            }
            trackValue->setText(QString("%1 %").arg(trackContinuity, 0, 'f', 1));
        }
        
        // 更新探测中断原因
        if (reasonValue) {
            QString reason;
            if (conditionComboBox->currentIndex() == 0) { // 无干扰
                reason = "无干扰影响";
            } else if (conditionComboBox->currentIndex() == 1) { // 有干扰
                reason = "受欺骗式干扰影响";
            } else if (conditionComboBox->currentIndex() == 2) { // 抗干扰
                reason = "抗干扰措施有效，影响较小";
            }
            reasonValue->setText(reason);
        }
    } catch (const std::exception& e) {
        if (distanceValue) {
            distanceValue->setText("计算失败: " + QString(e.what()));
        } else {
            QMessageBox::warning(this, "错误", "计算失败: " + QString(e.what()));
        }
        // 计算失败时重置其他结果
        if (trackValue) {
            trackValue->setText("--");
        }
        if (reasonValue) {
            reasonValue->setText("--");
        }
    } catch (...) {
        if (distanceValue) {
            distanceValue->setText("计算失败: 未知错误");
        } else {
            QMessageBox::warning(this, "错误", "计算失败: 未知错误");
        }
        // 计算失败时重置其他结果
        if (trackValue) {
            trackValue->setText("--");
        }
        if (reasonValue) {
            reasonValue->setText("--");
        }
    }
}
//编队评估计算
void DetectionPerformanceView::onFormationEvaluate() {
    // 验证输入
    if (static_cast<int>(currentFormationRadars.size()) < 2) {
        QMessageBox::warning(this, "错误", "请至少选择两个探测模型");
        return;
    }
    if (static_cast<int>(currentFormationRadars.size()) > 4) {
        QMessageBox::warning(this, "错误", "最多选择四个探测模型");
        return;
    }
    
    if (formationConditionComboBox->currentIndex() != 0 && !currentFormationJammer) {
        QMessageBox::warning(this, "错误", "请选择干扰模型");
        return;
    }
    
    if (!currentFormationTarget) {
        QMessageBox::warning(this, "错误", "请选择目标模型");
        return;
    }
    
    try {
        // 将指针集合拷贝为值集合
        std::vector<RadarModel> radars;
        radars.reserve(currentFormationRadars.size());
        for (RadarModel* ptr : currentFormationRadars) {
            if (ptr) radars.push_back(*ptr);
        }
        // 固定RCS=50
        RcsData fixedRcs; fixedRcs.rcs_value = 50.0; fixedRcs.azimuth = 0; fixedRcs.elevation = 0;
        double distance = FormationEvaluationController::evaluateFormation(
            formationConditionComboBox->currentIndex(),
            radars,
            currentFormationJammer,
            *currentFormationTarget,
            fixedRcs
        );
        //更新探测距离
        if (formationDistanceValue) {
            // 显示计算结果，保留2位小数
            formationDistanceValue->setText(QString("%1 米").arg(distance, 0, 'f', 2));
        } else {
            // 容错处理：如果未找到控件，显示错误信息
            QMessageBox::warning(this, "错误", "编队评估结果区域未初始化");
        }
        
        // 更新目标航迹连续性
        if (formationTrackValue) {
            // 根据干扰情况和探测数量设置不同的航迹连续性值
            double trackContinuity = 95.0; // 默认值
            if (formationConditionComboBox->currentIndex() == 1) { // 有干扰
                trackContinuity = 80.0 + currentFormationRadars.size() * 2.0; // 探测数量越多，连续性越好
            } else if (formationConditionComboBox->currentIndex() == 2) { // 抗干扰
                trackContinuity = 88.0 + currentFormationRadars.size() * 1.5;
            } else { // 无干扰
                trackContinuity = 92.0 + currentFormationRadars.size() * 1.0;
            }
            // 限制最大值
            if (trackContinuity > 98.0) trackContinuity = 98.0;
            formationTrackValue->setText(QString("%1 %").arg(trackContinuity, 0, 'f', 1));
        }
        
        // 更新探测中断原因
        if (formationReasonValue) {
            QString reason;
            if (formationConditionComboBox->currentIndex() == 0) { // 无干扰
                reason = "无干扰影响，编队协同探测效果良好";
            } else if (formationConditionComboBox->currentIndex() == 1) { // 有干扰
                reason = "受欺骗式干扰影响，编队协同可部分抵消干扰";
            } else if (formationConditionComboBox->currentIndex() == 2) { // 抗干扰
                reason = "抗干扰措施有效，编队协同进一步提升抗干扰能力";
            }
            formationReasonValue->setText(reason);
        }
        // formationResultLabel->setText(QString("探测距离: %1 米").arg(distance, 0, 'f', 2));
    } catch (const std::exception& e) {
        if (formationDistanceValue) {
            formationDistanceValue->setText("计算失败: " + QString(e.what()));
        } else {
            QMessageBox::warning(this, "错误", "编队计算失败: " + QString(e.what()));
        }
        // 计算失败时重置其他结果
        if (formationTrackValue) {
            formationTrackValue->setText("--");
        }
        if (formationReasonValue) {
            formationReasonValue->setText("--");
        }
    } catch (...) {
        if (formationDistanceValue) {
            formationDistanceValue->setText("计算失败: 未知错误");
        } else {
            QMessageBox::warning(this, "错误", "编队计算失败: 未知错误");
        }
        // 计算失败时重置其他结果
        if (formationTrackValue) {
            formationTrackValue->setText("--");
        }
        if (formationReasonValue) {
            formationReasonValue->setText("--");
        }
    }
}
//更新模型展示
void DetectionPerformanceView::updateModelDisplay() {
    radarLabel->setText(currentRadar ? QString::fromStdString(currentRadar->name) : "未选择");
    jammerLabel->setText(currentJammer ? QString::fromStdString(currentJammer->name) : "未选择");
    targetLabel->setText(currentTarget ? QString::fromStdString(currentTarget->name) : "未选择");
}
//更新编队评估模型展示
void DetectionPerformanceView::updateFormationModelDisplay() {
    if (currentFormationRadars.empty()) {
        formationRadarLabel->setText("未选择");
    } else {
        QStringList names;
        for (size_t i = 0; i < currentFormationRadars.size(); ++i) {
            RadarModel* ptr = currentFormationRadars[i];
            if (ptr) names << QString::fromStdString(ptr->name);
        }
        formationRadarLabel->setText(QString("%1 (已选%2/4)").arg(names.join("，")).arg(currentFormationRadars.size()));
    }
    addFormationRadarButton->setEnabled(static_cast<int>(currentFormationRadars.size()) < 4);
    deleteFormationRadarButton->setEnabled(!currentFormationRadars.empty());
    formationJammerLabel->setText(currentFormationJammer ? 
        QString::fromStdString(currentFormationJammer->name) : "未选择");
    formationTargetLabel->setText(currentFormationTarget ? 
        QString::fromStdString(currentFormationTarget->name) : "未选择");
}
//展示单机评估中探测模型详情
void DetectionPerformanceView::showRadarDetails() {
    if (currentRadar) {
        QString details = QString("探测模型: %1\n"
                                 "波长: %2 m\n"
                                 "发射功率: %3 KW\n"
                                 "信号带宽: %4 MHz\n"
                                 "天线增益: %5 dB\n"
                                 "系统损耗因子: %6\n"
                                 "位置: (%7, %8, %9)\n"
                                 "航向: %10\n"
                                 "飞行速度: %11")
                         .arg(QString::fromStdString(currentRadar->name))
                         .arg(currentRadar->wavelength)
                         .arg(currentRadar->power)
                         .arg(currentRadar->bandwidth)
                         .arg(currentRadar->gain)
                         .arg(currentRadar->loss_factor)
                         .arg(currentRadar->longitude)
                         .arg(currentRadar->latitude)
                         .arg(currentRadar->altitude)
                         .arg(currentRadar->heading, 0, 'f', 2)
                         .arg(currentRadar->speed, 0, 'f', 2);
        QMessageBox::information(this, "探测模型详情", details);
    }
}
//展示单机评估中干扰模型详情
void DetectionPerformanceView::showJammerDetails() {
    if (currentJammer) {
        QString details = QString("干扰模型: %1\n"
                                 "干扰样式: %2\n"
                                 "干扰功率: %3 W\n"
                                 "干扰带宽: %4 MHz\n"
                                 "干扰增益: %5 dB\n"
                                 "位置: (%6, %7, %8)\n"
                                 "航向: %9\n"
                                 "飞行速度: %10")
                         .arg(QString::fromStdString(currentJammer->name))
                         .arg(QString::fromStdString(currentJammer->jamming_type))
                         .arg(currentJammer->power)
                         .arg(currentJammer->bandwidth)
                         .arg(currentJammer->gain)
                         .arg(currentJammer->longitude)
                         .arg(currentJammer->latitude)
                         .arg(currentJammer->altitude)
                         .arg(currentJammer->heading, 0, 'f', 2)
                         .arg(currentJammer->speed, 0, 'f', 2);
        QMessageBox::information(this, "干扰机模型详情", details);
    }
}
//展示单机评估中目标模型详情
void DetectionPerformanceView::showTargetDetails() {
    if (currentTarget) {
        QString details = QString("目标模型: %1\n"
                                 "目标类型: %2\n"
                                 "位置: (%3, %4, %5)\n"
                                 "航向: %6\n"
                                 "飞行速度: %7")
                         .arg(QString::fromStdString(currentTarget->name))
                         .arg(QString::fromStdString(currentTarget->target_type))
                         .arg(currentTarget->longitude)
                         .arg(currentTarget->latitude)
                         .arg(currentTarget->altitude)
                         .arg(currentTarget->heading, 0, 'f', 2)
                         .arg(currentTarget->speed, 0, 'f', 2);
                         
        // 如果探测模型已选择，显示距离
        if (currentRadar) {
            double distance = calculateSpatialDistance(
                currentRadar->longitude, currentRadar->latitude, currentRadar->altitude,
                currentTarget->longitude, currentTarget->latitude, currentTarget->altitude
            );
            details += QString("\n与探测距离: %1 米").arg(distance, 0, 'f', 2);
        }
        
        QMessageBox::information(this, "目标模型详情", details);
    }
}
//展示编队评估中探测模型详情
void DetectionPerformanceView::showFormationRadarDetails() {
    if (!currentFormationRadars.empty()) {
        QString details;
        for (size_t i = 0; i < currentFormationRadars.size(); ++i) {
            RadarModel* r = currentFormationRadars[i];
            if (!r) continue;
            details += QString("[%1] 探测模型: %2\n"
                               "波长: %3 m\n"
                               "发射功率: %4 KW\n"
                               "信号带宽: %5 MHz\n"
                               "天线增益: %6 dB\n"
                               "系统损耗因子: %7\n"
                               "位置: (%8, %9, %10)\n\n")
                       .arg(i + 1)
                       .arg(QString::fromStdString(r->name))
                       .arg(r->wavelength)
                       .arg(r->power)
                       .arg(r->bandwidth)
                       .arg(r->gain)
                       .arg(r->loss_factor)
                       .arg(r->longitude)
                       .arg(r->latitude)
                       .arg(r->altitude);
        }
        QMessageBox::information(this, "探测模型详情", details);
    }
}
//展示编队评估中干扰模型详情
void DetectionPerformanceView::showFormationJammerDetails() {
    if (currentFormationJammer) {
        QString details = QString("干扰模型: %1\n"
                                 "干扰样式: %2\n"
                                 "干扰功率: %3 W\n"
                                 "干扰带宽: %4 MHz\n"
                                 "干扰增益: %5 dB\n"
                                 "位置: (%6, %7, %8)\n"
                                 "航向: %9\n"
                                 "飞行速度: %10")
                         .arg(QString::fromStdString(currentFormationJammer->name))
                         .arg(QString::fromStdString(currentFormationJammer->jamming_type))
                         .arg(currentFormationJammer->power)
                         .arg(currentFormationJammer->bandwidth)
                         .arg(currentFormationJammer->gain)
                         .arg(currentFormationJammer->longitude)
                         .arg(currentFormationJammer->latitude)
                         .arg(currentFormationJammer->altitude)
                         .arg(currentFormationJammer->heading, 0, 'f', 2)
                         .arg(currentFormationJammer->speed, 0, 'f', 2);
        QMessageBox::information(this, "干扰机模型详情", details);
    }
}
//展示编队评估中目标模型详情
void DetectionPerformanceView::showFormationTargetDetails() {
    if (currentFormationTarget) {
        QString details = QString("目标模型: %1\n"
                                 "目标类型: %2\n"
                                 "位置: (%3, %4, %5)\n"
                                 "航向: %6\n"
                                 "飞行速度: %7")
                         .arg(QString::fromStdString(currentFormationTarget->name))
                         .arg(QString::fromStdString(currentFormationTarget->target_type))
                         .arg(currentFormationTarget->longitude)
                         .arg(currentFormationTarget->latitude)
                         .arg(currentFormationTarget->altitude)
                         .arg(currentFormationTarget->heading, 0, 'f', 2)
                         .arg(currentFormationTarget->speed, 0, 'f', 2);     
        QMessageBox::information(this, "目标模型详情", details);
    }
}
//计算距离
double DetectionPerformanceView::calculateSpatialDistance(
    double lon1, double lat1, double alt1, 
    double lon2, double lat2, double alt2){
    // 地球半径（米）
    const double R = 6371000.0;
    
    // 将经纬度转换为弧度
    double lat1Rad = lat1 * M_PI / 180.0;
    double lon1Rad = lon1 * M_PI / 180.0;
    double lat2Rad = lat2 * M_PI / 180.0;
    double lon2Rad = lon2 * M_PI / 180.0;
    
    // 计算差值
    double dLat = lat2Rad - lat1Rad;
    double dLon = lon2Rad - lon1Rad;
    
    // Haversine公式计算球面距离
    double a = sin(dLat/2) * sin(dLat/2) +
               cos(lat1Rad) * cos(lat2Rad) * 
               sin(dLon/2) * sin(dLon/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    double distance = R * c;
    
    // 考虑高度差（直角坐标）
    double dAlt = alt2 - alt1;
    return sqrt(distance * distance + dAlt * dAlt);
}