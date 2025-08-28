#include "DetectionPerformanceView.h"
#include "ModelSelectionDialog.h"
#include "SingleEvaluationController.h"
#include "FormationEvaluationController.h"
#include <QMessageBox>
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
    QGroupBox *conditionGroup = new QGroupBox("评估条件", this);
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
    
    selectRadarButton = new QPushButton("选择雷达模型", this);
    selectJammerButton = new QPushButton("选择干扰模型", this);
    selectTargetButton = new QPushButton("选择目标模型", this);
    evaluateButton = new QPushButton("评估", this);
    
    radarLabel = new QLabel("未选择", this);
    jammerLabel = new QLabel("未选择", this);
    targetLabel = new QLabel("未选择", this);
    
    
    QPushButton *radarDetailButton = new QPushButton("查看", this);
    QPushButton *jammerDetailButton = new QPushButton("查看", this);
    QPushButton *targetDetailButton = new QPushButton("查看", this);
    
    modelLayout->addWidget(new QLabel("雷达模型:"), 0, 0);
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
    QVBoxLayout *resultLayout = new QVBoxLayout;
    resultLabel = new QLabel("结果将显示在这里", this);
    resultLabel->setAlignment(Qt::AlignCenter);
    resultLayout->addWidget(resultLabel);
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
    QGroupBox *conditionGroup = new QGroupBox("评估条件", this);
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
    
    selectFormationRadarButton = new QPushButton("选择雷达模型", this);
    addFormationRadarButton = new QPushButton("增加", this);
    selectFormationJammerButton = new QPushButton("选择干扰模型", this);
    selectFormationTargetButton = new QPushButton("选择目标模型", this);
    formationEvaluateButton = new QPushButton("评估", this);
    
    formationRadarLabel = new QLabel("未选择", this);
    formationJammerLabel = new QLabel("未选择", this);
    formationTargetLabel = new QLabel("未选择", this);
    
    
    QPushButton *formationRadarDetailButton = new QPushButton("查看", this);
    QPushButton *formationJammerDetailButton = new QPushButton("查看", this);
    QPushButton *formationTargetDetailButton = new QPushButton("查看", this);
    
    modelLayout->addWidget(new QLabel("雷达模型:"), 0, 0);
    modelLayout->addWidget(formationRadarLabel, 0, 1);
    modelLayout->addWidget(selectFormationRadarButton, 0, 2);
    modelLayout->addWidget(formationRadarDetailButton, 0, 3);
    modelLayout->addWidget(addFormationRadarButton, 0, 4);
    
    modelLayout->addWidget(new QLabel("干扰模型:"), 2, 0);
    modelLayout->addWidget(formationJammerLabel, 2, 1);
    modelLayout->addWidget(selectFormationJammerButton, 2, 2);
    modelLayout->addWidget(formationJammerDetailButton, 2, 3);
    
    modelLayout->addWidget(new QLabel("目标模型:"), 3, 0);
    modelLayout->addWidget(formationTargetLabel, 3, 1);
    modelLayout->addWidget(selectFormationTargetButton, 3, 2);
    modelLayout->addWidget(formationTargetDetailButton, 3, 3);
    
    modelLayout->addWidget(formationEvaluateButton, 4, 0, 1, 5);
    modelGroup->setLayout(modelLayout);
    
    // 结果展示
    QGroupBox *resultGroup = new QGroupBox("评估结果", this);
    QVBoxLayout *resultLayout = new QVBoxLayout;
    formationResultLabel = new QLabel("结果将显示在这里", this);
    formationResultLabel->setAlignment(Qt::AlignCenter);
    resultLayout->addWidget(formationResultLabel);
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

void DetectionPerformanceView::onSelectFormationRadar() {
    isAddingFormationRadar = false;
    if (!radarDialogForFormationRadar) {
        radarDialogForFormationRadar = new ModelSelectionDialog(this);
        radarDialogForFormationRadar->setModels(SingleEvaluationController::getAllRadarModels());
        connect(radarDialogForFormationRadar, &ModelSelectionDialog::modelSelected, [this](const QVariant& model) {
            RadarModel* newRadar = new RadarModel(model.value<RadarModel>());
            if (isAddingFormationRadar) {
                if (static_cast<int>(currentFormationRadars.size()) >= 4) {
                    QMessageBox::warning(this, "提示", "最多可选择四个雷达模型");
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

void DetectionPerformanceView::onAddFormationRadar() {
    if (static_cast<int>(currentFormationRadars.size()) >= 4) {
        QMessageBox::warning(this, "提示", "最多可选择四个雷达模型");
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
                    QMessageBox::warning(this, "提示", "最多可选择四个雷达模型");
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

void DetectionPerformanceView::onSelectFormationJammer() {
    if (!jammerDialog) {
        jammerDialog = new ModelSelectionDialog(this);
        jammerDialog->setModels(SingleEvaluationController::getAllJammerModels());
        connect(jammerDialog, &ModelSelectionDialog::modelSelected, [this](const QVariant& model) {
            delete currentFormationJammer;
            currentFormationJammer = new JammerModel(model.value<JammerModel>());
            updateFormationModelDisplay();
        });
    }
    jammerDialog->show();
}

void DetectionPerformanceView::onSelectFormationTarget() {
    if (!targetDialog) {
        targetDialog = new ModelSelectionDialog(this);
        targetDialog->setModels(SingleEvaluationController::getAllTargetModels(), false);
        connect(targetDialog, &ModelSelectionDialog::modelSelected, [this](const QVariant& model) {
            delete currentFormationTarget;
            currentFormationTarget = new TargetModel(model.value<TargetModel>());
            
            updateFormationModelDisplay();
        });
    }
    targetDialog->show();
}

void DetectionPerformanceView::onEvaluate() {
    // 验证输入
    if (!currentRadar) {
        QMessageBox::warning(this, "错误", "请选择雷达模型");
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
    
    // 计算雷达与目标的空间距离
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
        
        resultLabel->setText(QString("探测距离: %1 米").arg(resultDistance, 0, 'f', 2));
    } catch (const std::exception& e) {
        resultLabel->setText("计算失败: " + QString(e.what()));
    } catch (...) {
        resultLabel->setText("计算失败: 未知错误");
    }
}

void DetectionPerformanceView::onFormationEvaluate() {
    // 验证输入
    if (static_cast<int>(currentFormationRadars.size()) < 2) {
        QMessageBox::warning(this, "错误", "请至少选择两个雷达模型");
        return;
    }
    if (static_cast<int>(currentFormationRadars.size()) > 4) {
        QMessageBox::warning(this, "错误", "最多选择四个雷达模型");
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
        
        formationResultLabel->setText(QString("探测距离: %1 米").arg(distance, 0, 'f', 2));
    } catch (const std::exception& e) {
        formationResultLabel->setText("计算失败: " + QString(e.what()));
    } catch (...) {
        formationResultLabel->setText("计算失败: 未知错误");
    }
}

void DetectionPerformanceView::updateModelDisplay() {
    radarLabel->setText(currentRadar ? QString::fromStdString(currentRadar->name) : "未选择");
    jammerLabel->setText(currentJammer ? QString::fromStdString(currentJammer->name) : "未选择");
    targetLabel->setText(currentTarget ? QString::fromStdString(currentTarget->name) : "未选择");
}

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
    formationJammerLabel->setText(currentFormationJammer ? 
        QString::fromStdString(currentFormationJammer->name) : "未选择");
    formationTargetLabel->setText(currentFormationTarget ? 
        QString::fromStdString(currentFormationTarget->name) : "未选择");
}

void DetectionPerformanceView::showRadarDetails() {
    if (currentRadar) {
        QString details = QString("雷达模型: %1\n"
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
        QMessageBox::information(this, "雷达模型详情", details);
    }
}

void DetectionPerformanceView::showJammerDetails() {
    if (currentJammer) {
        QString details = QString("干扰机模型: %1\n"
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
                         
        
        // 不显示RCS信息
        // 如果雷达模型已选择，显示距离
        if (currentRadar) {
            double distance = calculateSpatialDistance(
                currentRadar->longitude, currentRadar->latitude, currentRadar->altitude,
                currentTarget->longitude, currentTarget->latitude, currentTarget->altitude
            );
            details += QString("\n与雷达距离: %1 米").arg(distance, 0, 'f', 2);
        }
        
        QMessageBox::information(this, "目标模型详情", details);
    }
}

void DetectionPerformanceView::showFormationRadarDetails() {
    if (!currentFormationRadars.empty()) {
        QString details;
        for (size_t i = 0; i < currentFormationRadars.size(); ++i) {
            RadarModel* r = currentFormationRadars[i];
            if (!r) continue;
            details += QString("[%1] 雷达模型: %2\n"
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
        QMessageBox::information(this, "雷达模型详情", details);
    }
}

void DetectionPerformanceView::showFormationJammerDetails() {
    if (currentFormationJammer) {
        QString details = QString("干扰机模型: %1\n"
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
                         
        
        // 不显示RCS信息
        
        QMessageBox::information(this, "目标模型详情", details);
    }
}

double DetectionPerformanceView::calculateSpatialDistance(
    double lon1, double lat1, double alt1, 
    double lon2, double lat2, double alt2) 
{
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