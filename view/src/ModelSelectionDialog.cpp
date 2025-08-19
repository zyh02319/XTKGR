#include "ModelSelectionDialog.h"
#include <QMessageBox>
#include "SingleEvaluationController.h"
#include <cmath>

// // 在包含头文件后声明元类型
// #include "RadarModelDAO.h"
// #include "JammerModelDAO.h"
// #include "TargetModelDAO.h"
// #include "RcsDataDAO.h"

// Q_DECLARE_METATYPE(RadarModel)
// Q_DECLARE_METATYPE(JammerModel)
// Q_DECLARE_METATYPE(TargetModel)
// Q_DECLARE_METATYPE(RcsData)

ModelSelectionDialog::ModelSelectionDialog(QWidget *parent, bool isTarget)
    : QDialog(parent), isTargetModel(isTarget)
{
    setWindowTitle("选择模型");
    setMinimumSize(600, 400);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    stackedWidget = new QStackedWidget(this);
    
    // 模型列表
    modelList = new QListWidget(this);
    modelList->setSelectionMode(QListWidget::SingleSelection);
    
    // RCS列表（仅用于目标模型）
    rcsList = new QListWidget(this);
    rcsList->setSelectionMode(QListWidget::SingleSelection);
    
    stackedWidget->addWidget(modelList);
    stackedWidget->addWidget(rcsList);
    
    // 按钮
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    // 添加返回按钮
    returnButton = new QPushButton("返回", this);
     // 初始时隐藏返回按钮
    returnButton->setVisible(false);
    
    // 将返回按钮添加到按钮框
    buttonBox->addButton(returnButton, QDialogButtonBox::ActionRole);
    
    mainLayout->addWidget(stackedWidget);
    mainLayout->addWidget(buttonBox);

    // 连接返回按钮的信号
    connect(returnButton, &QPushButton::clicked, this, &ModelSelectionDialog::onReturn);
    
    connect(modelList, &QListWidget::itemClicked, this, &ModelSelectionDialog::onModelSelected);
    connect(rcsList, &QListWidget::itemClicked, this, &ModelSelectionDialog::onRcsSelected);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &ModelSelectionDialog::onAccept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}


// 添加返回处理函数
// void ModelSelectionDialog::onReturn() {
//     stackedWidget->setCurrentIndex(0); // 返回模型选择页面
// }
// 添加返回处理函数实现
void ModelSelectionDialog::onReturn() {
    stackedWidget->setCurrentIndex(0); // 返回模型选择页面
    returnButton->setVisible(false);
    if (buttonBox->button(QDialogButtonBox::Ok)) {
        buttonBox->button(QDialogButtonBox::Ok)->setVisible(true);
    }
}

void ModelSelectionDialog::setModels(const std::vector<RadarModel>& models) {
    radarModels = models;
    modelList->clear();
    for (const auto& model : models) {
        modelList->addItem(QString::fromStdString(model.name));
    }
    stackedWidget->setCurrentIndex(0);
}

void ModelSelectionDialog::setModels(const std::vector<JammerModel>& models) {
    jammerModels = models;
    modelList->clear();
    for (const auto& model : models) {
        modelList->addItem(QString::fromStdString(model.name));
    }
    stackedWidget->setCurrentIndex(0);
}

void ModelSelectionDialog::setModels(const std::vector<TargetModel>& models, bool showRcs) {
    targetModels = models;
    isTargetModel = showRcs;
    modelList->clear();
    for (const auto& model : models) {
        modelList->addItem(QString::fromStdString(model.name));
    }
    stackedWidget->setCurrentIndex(0);
}

void ModelSelectionDialog::onModelSelected(QListWidgetItem *item) {
    // if (!isTargetModel) return;
    
    // int row = modelList->row(item);
    // if (row < 0 || row >= static_cast<int>(targetModels.size())) return;
    
    // // 加载RCS数据
    // currentRcsData = SingleEvaluationController::getRcsDataByTargetId(targetModels[row].id);
    // rcsList->clear();
    
    // for (const auto& rcs : currentRcsData) {
    //     rcsList->addItem(QString("方位角: %1°, 俯仰角: %2°, RCS: %3 m²")
    //                     .arg(rcs.azimuth).arg(rcs.elevation).arg(rcs.rcs_value));
    // }
    
    // stackedWidget->setCurrentIndex(1);
    //  // 显示返回按钮，隐藏确定按钮
    // // returnButton->setVisible(true);
    // // buttonBox->button(QDialogButtonBox::Ok)->setVisible(false);
    // // 显示返回按钮，隐藏确定按钮
    // if (returnButton) {
    //     returnButton->setVisible(true);
    // }
    // if (buttonBox->button(QDialogButtonBox::Ok)) {
    //     buttonBox->button(QDialogButtonBox::Ok)->setVisible(false);
    // }
     if (!isTargetModel) return;
    
    int row = modelList->row(item);
    if (row < 0 || row >= static_cast<int>(targetModels.size())) return;
    
    // 加载RCS数据前先发送目标模型选择的信号
    selectedTargetModel = targetModels[row];  // 保存选中的目标模型
    emit modelSelected(QVariant::fromValue(selectedTargetModel));  // 发送信号
    
    // 然后加载RCS数据
    currentRcsData = SingleEvaluationController::getRcsDataByTargetId(targetModels[row].id);
    rcsList->clear();
    
    for (const auto& rcs : currentRcsData) {
        rcsList->addItem(QString("方位角: %1°, 俯仰角: %2°, RCS: %3 m²")
                        .arg(rcs.azimuth).arg(rcs.elevation).arg(rcs.rcs_value));
    }
    
    stackedWidget->setCurrentIndex(1);
    // 显示返回按钮，隐藏确定按钮
    if (returnButton) {
        returnButton->setVisible(true);
    }
    if (buttonBox->button(QDialogButtonBox::Ok)) {
        buttonBox->button(QDialogButtonBox::Ok)->setVisible(false);
    }
}

void ModelSelectionDialog::onRcsSelected(QListWidgetItem *item) {
    int row = rcsList->row(item);
    if (row >= 0 && row < static_cast<int>(currentRcsData.size())) {
        emit rcsSelected(currentRcsData[row]);
    }
}

void ModelSelectionDialog::onAccept() {
    if (stackedWidget->currentIndex() == 1) {
        // 在RCS选择页面
        // if (rcsList->currentItem()) {
        //     int row = rcsList->currentRow();
        //     if (row >= 0 && row < static_cast<int>(currentRcsData.size())) {
        //         emit rcsSelected(currentRcsData[row]);
        //     }
        // } else {
        //     QMessageBox::warning(this, "警告", "请选择一个RCS数据");
        //     return;
        // }
        // 在RCS选择页面
        if (rcsList->currentItem()) {
            int row = rcsList->currentRow();
            if (row >= 0 && row < static_cast<int>(currentRcsData.size())) {
                // 确保目标模型信号已发送
                if (isTargetModel) {
                    emit modelSelected(QVariant::fromValue(selectedTargetModel));
                }
                emit rcsSelected(currentRcsData[row]);
            }
        } else {
            QMessageBox::warning(this, "警告", "请选择一个RCS数据");
            return;
        }
    } else {
        // 在模型选择页面，确保返回按钮隐藏，确定按钮显示
        // returnButton->setVisible(false);
        // buttonBox->button(QDialogButtonBox::Ok)->setVisible(true);
        if (returnButton) {
            returnButton->setVisible(false);
        }
        if (buttonBox->button(QDialogButtonBox::Ok)) {
            buttonBox->button(QDialogButtonBox::Ok)->setVisible(true);
        }
        // 在模型选择页面
        if (modelList->currentItem()) {
            
            int row = modelList->currentRow();
            if (!radarModels.empty() && row < static_cast<int>(radarModels.size())) {
                emit modelSelected(QVariant::fromValue(radarModels[row]));
            } else if (!jammerModels.empty() && row < static_cast<int>(jammerModels.size())) {
                emit modelSelected(QVariant::fromValue(jammerModels[row]));
            } else if (!targetModels.empty() && row < static_cast<int>(targetModels.size())) {
                emit modelSelected(QVariant::fromValue(targetModels[row]));
            }
        } else {
            QMessageBox::warning(this, "警告", "请选择一个模型");
            return;
        }
    }
    accept();
}