#include "TargetModelEditDialog.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QLabel>
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QAbstractItemView>
#include <QStringList>
#include <QComboBox> 
#include <QDoubleSpinBox>
#include "RcsEditDialog.h"
#include "ModelManageController.h"

TargetModelEditDialog::TargetModelEditDialog(QWidget *parent)
    : QDialog(parent), targetId(-1), isEditMode(false) {
    initUI();
}

TargetModelEditDialog::TargetModelEditDialog(int targetId, QWidget *parent)
    : QDialog(parent), targetId(targetId), isEditMode(true) {
    initUI();
    loadTargetData();
    loadRcsData();
}

void TargetModelEditDialog::initUI() {
    setWindowTitle(isEditMode ? "编辑目标模型" : "新建目标模型");
    setMinimumSize(600, 500);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // === 目标模型表单 ===
    QGroupBox *targetGroup = new QGroupBox("目标模型参数");
    QFormLayout *formLayout = new QFormLayout;
    
    nameEdit = new QLineEdit;
    // typeEdit = new QLineEdit;
    typeCombo = new QComboBox; 
    // longitudeEdit = new QLineEdit;
    // latitudeEdit = new QLineEdit;
    // altitudeEdit = new QLineEdit;
    longitudeSpin = new QDoubleSpinBox;
    longitudeSpin->setRange(-180, 180); // 经度范围
    longitudeSpin->setDecimals(6);      // 小数位数
    longitudeSpin->setSingleStep(0.1);  // 步长
    
    latitudeSpin = new QDoubleSpinBox;
    latitudeSpin->setRange(-90, 90);    // 纬度范围
    latitudeSpin->setDecimals(6);
    latitudeSpin->setSingleStep(0.1);
    
    altitudeSpin = new QDoubleSpinBox;
    altitudeSpin->setRange(-10000, 100000); // 高度范围
    altitudeSpin->setDecimals(2);
    altitudeSpin->setSingleStep(1);
    altitudeSpin->setSuffix(" m");       // 单位

    headingSpin = new QDoubleSpinBox;
    headingSpin->setRange(0, 360);
    headingSpin->setDecimals(2);
    headingSpin->setSuffix(" °");
    
    speedSpin = new QDoubleSpinBox;
    speedSpin->setRange(0, 100000);
    speedSpin->setDecimals(2);
    speedSpin->setSuffix(" km/h");

     // 添加目标类型选项（根据 SQL 文件定义）
    typeCombo->addItem("空中");
    typeCombo->addItem("地面");
    typeCombo->addItem("海上");
    typeCombo->addItem("太空");
    
    formLayout->addRow("名称:", nameEdit);
    formLayout->addRow("类型:", typeCombo); // 修改为 typeCombo
    // formLayout->addRow("类型:", typeEdit);
    // formLayout->addRow("经度:", longitudeEdit);
    // formLayout->addRow("纬度:", latitudeEdit);
    // formLayout->addRow("高度:", altitudeEdit);
    formLayout->addRow("经度:", longitudeSpin);
    formLayout->addRow("纬度:", latitudeSpin);
    formLayout->addRow("高度:", altitudeSpin);
    formLayout->addRow("航向:", headingSpin);
    formLayout->addRow("飞行速度:", speedSpin);
    
    targetGroup->setLayout(formLayout);
    mainLayout->addWidget(targetGroup);
    
    // === 保存目标按钮 ===
    QPushButton *saveTargetBtn = new QPushButton("保存目标模型");
    connect(saveTargetBtn, &QPushButton::clicked, this, &TargetModelEditDialog::onSaveTarget);
    mainLayout->addWidget(saveTargetBtn);
    
    // === RCS数据管理 ===
    QGroupBox *rcsGroup = new QGroupBox("RCS数据管理");
    QVBoxLayout *rcsLayout = new QVBoxLayout;
    
    rcsTable = new QTableWidget;
    rcsTable->setColumnCount(3);
    rcsTable->setHorizontalHeaderLabels(QStringList() << "方位角" << "俯仰角" << "RCS值");
    rcsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    rcsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    rcsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    
    rcsLayout->addWidget(rcsTable);
    
    QHBoxLayout *rcsButtonLayout = new QHBoxLayout;
    QPushButton *createRcsBtn = new QPushButton("新建RCS");
    editRcsBtn = new QPushButton("编辑RCS");
    deleteRcsBtn = new QPushButton("删除RCS");
    
    editRcsBtn->setEnabled(false);
    deleteRcsBtn->setEnabled(false);
    
    connect(createRcsBtn, &QPushButton::clicked, this, &TargetModelEditDialog::onCreateRcs);
    connect(editRcsBtn, &QPushButton::clicked, this, &TargetModelEditDialog::onEditRcs);
    connect(deleteRcsBtn, &QPushButton::clicked, this, &TargetModelEditDialog::onDeleteRcs);
    connect(rcsTable, &QTableWidget::itemSelectionChanged, this, &TargetModelEditDialog::onRcsSelectionChanged);
    
    rcsButtonLayout->addWidget(createRcsBtn);
    rcsButtonLayout->addWidget(editRcsBtn);
    rcsButtonLayout->addWidget(deleteRcsBtn);
    rcsButtonLayout->addStretch();
    
    rcsLayout->addLayout(rcsButtonLayout);
    rcsGroup->setLayout(rcsLayout);
    mainLayout->addWidget(rcsGroup);
    
    setLayout(mainLayout);
}

void TargetModelEditDialog::loadTargetData() {
    if (isEditMode) {
        currentModel = ModelManageController::getTargetModelById(targetId);
        nameEdit->setText(QString::fromStdString(currentModel.name));
        // typeEdit->setText(QString::fromStdString(currentModel.target_type));
         // 设置当前选中的类型
        int index = typeCombo->findText(QString::fromStdString(currentModel.target_type));
        if (index >= 0) {
            typeCombo->setCurrentIndex(index);
        }
        // longitudeEdit->setText(QString::number(currentModel.longitude));
        // latitudeEdit->setText(QString::number(currentModel.latitude));
        // altitudeEdit->setText(QString::number(currentModel.altitude));
        longitudeSpin->setValue(currentModel.longitude);
        latitudeSpin->setValue(currentModel.latitude);
        altitudeSpin->setValue(currentModel.altitude);
        headingSpin->setValue(currentModel.heading);
        speedSpin->setValue(currentModel.speed);
    }
}

void TargetModelEditDialog::loadRcsData() {
    if (!isEditMode) return;
    
    rcsTable->setRowCount(0);
    std::vector<RcsData> rcsList = ModelManageController::getRcsDataByTargetId(targetId);
    
    for (const auto& rcs : rcsList) {
        int row = rcsTable->rowCount();
        rcsTable->insertRow(row);
        
        rcsTable->setItem(row, 0, new QTableWidgetItem(QString::number(rcs.azimuth)));
        rcsTable->setItem(row, 1, new QTableWidgetItem(QString::number(rcs.elevation)));
        rcsTable->setItem(row, 2, new QTableWidgetItem(QString::number(rcs.rcs_value)));
    }
}

TargetModel TargetModelEditDialog::getTargetModel() const {
    TargetModel model;
    if (isEditMode) model.id = targetId;
    model.name = nameEdit->text().toStdString();
    // model.target_type = typeEdit->text().toStdString();
    model.target_type = typeCombo->currentText().toStdString(); // 使用下拉框的值
    // model.longitude = longitudeEdit->text().toDouble();
    // model.latitude = latitudeEdit->text().toDouble();
    // model.altitude = altitudeEdit->text().toDouble();
    model.longitude = longitudeSpin->value();
    model.latitude = latitudeSpin->value();
    model.altitude = altitudeSpin->value();
    model.heading = headingSpin->value();
    model.speed = speedSpin->value();
    return model;
}

void TargetModelEditDialog::onSaveTarget() {
    TargetModel model = getTargetModel();
    
    bool success = false;
    if (isEditMode) {
        success = ModelManageController::updateTargetModel(model);
    } else {
        success = ModelManageController::createTargetModel(model);
    }
    
    if (success) {
        QMessageBox::information(this, "成功", isEditMode ? "目标模型更新成功" : "目标模型创建成功");
        accept(); // 关闭对话框
    } else {
        QMessageBox::warning(this, "错误", isEditMode ? "更新目标模型失败" : "创建目标模型失败");
    }
    // 防止重复保存
    // static bool isSaving = false;
    // if (isSaving) return;
    // isSaving = true;
    
    // TargetModel model = getTargetModel();
    
    // bool success = false;
    // if (isEditMode) {
    //     success = ModelManageController::updateTargetModel(model);
    // } else {
    //     success = ModelManageController::createTargetModel(model);
    //     if (success) {
    //         targetId = model.id; // 保存新创建的ID
    //         isEditMode = true; // 设置为编辑模式
    //     }
    // }
    
    // if (success) {
    //     QMessageBox::information(this, "成功", isEditMode ? "目标模型更新成功" : "目标模型创建成功");
    //     accept(); // 关闭对话框
    // } else {
    //     QMessageBox::warning(this, "错误", isEditMode ? "更新目标模型失败" : "创建目标模型失败");
    // }
    
    // isSaving = false;
    
}

void TargetModelEditDialog::onCreateRcs() {
    if (!isEditMode) return;
    
     // 错误修复：使用正确的参数调用构造函数
    // 原错误代码：RcsEditDialog dialog(-1, targetId);
    // 修正为：
    RcsEditDialog dialog(targetId, this); // 添加 this 作为父窗口指针
    if (dialog.exec() == QDialog::Accepted) {
        loadRcsData(); // 刷新RCS数据
    }
}

void TargetModelEditDialog::onEditRcs() {
   if (!isEditMode) return;
    
    int row = rcsTable->currentRow();
    if (row < 0) return;
    
    double azimuth = rcsTable->item(row, 0)->text().toDouble();
    double elevation = rcsTable->item(row, 1)->text().toDouble();
    
    // 错误修复：添加父窗口指针
    RcsEditDialog dialog(targetId, azimuth, elevation, this);
    if (dialog.exec() == QDialog::Accepted) {
        loadRcsData(); // 刷新RCS数据
    }
}

void TargetModelEditDialog::onDeleteRcs() {
    if (!isEditMode) return;
    
    int row = rcsTable->currentRow();
    if (row < 0) return;
    
    double azimuth = rcsTable->item(row, 0)->text().toDouble();
    double elevation = rcsTable->item(row, 1)->text().toDouble();
    
    if (QMessageBox::question(this, "确认", "确定要删除该RCS数据吗？") == QMessageBox::Yes) {
        if (ModelManageController::deleteRcsData(targetId, azimuth, elevation)) {
            loadRcsData(); // 刷新RCS数据
        } else {
            QMessageBox::warning(this, "错误", "删除RCS数据失败");
        }
    }
}

void TargetModelEditDialog::onRcsSelectionChanged() {
    bool hasSelection = !rcsTable->selectionModel()->selectedRows().isEmpty();
    editRcsBtn->setEnabled(hasSelection);
    deleteRcsBtn->setEnabled(hasSelection);
}