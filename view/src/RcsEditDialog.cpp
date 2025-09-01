#include "RcsEditDialog.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QDialogButtonBox>
#include "ModelManageController.h"
#include <QDoubleSpinBox>
#include <QMessageBox>

// 构造函数参数列表
RcsEditDialog::RcsEditDialog(int targetId, QWidget *parent)
    : QDialog(parent), targetId(targetId), originalAzimuth(0), 
      originalElevation(0), isEditMode(false) {
    initUI();
    setWindowTitle("新建RCS数据");
}

// 构造函数参数列表
RcsEditDialog::RcsEditDialog(int targetId, double azimuth, double elevation, QWidget *parent)
    : QDialog(parent), targetId(targetId), originalAzimuth(azimuth), 
      originalElevation(elevation), isEditMode(true) {
    initUI();
    loadData();
    setWindowTitle("编辑RCS数据");
}

void RcsEditDialog::initUI() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    QFormLayout *formLayout = new QFormLayout;
    
    azimuthSpin = new QDoubleSpinBox;
    azimuthSpin->setRange(0, 360);
    azimuthSpin->setSingleStep(1);
    
    elevationSpin = new QDoubleSpinBox;
    elevationSpin->setRange(-90, 90);
    elevationSpin->setSingleStep(1);
    
    rcsSpin = new QDoubleSpinBox;
    rcsSpin->setRange(0, 100000);
    rcsSpin->setSingleStep(0.0001);
    
    formLayout->addRow("方位角 (°):", azimuthSpin);
    formLayout->addRow("俯仰角 (°):", elevationSpin);
    formLayout->addRow("RCS值 (m²):", rcsSpin);
    
    mainLayout->addLayout(formLayout);
    
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &RcsEditDialog::onSaveRcs);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
}

void RcsEditDialog::loadData() {
    if (!isEditMode) return;
    
    azimuthSpin->setValue(originalAzimuth);
    elevationSpin->setValue(originalElevation);
    
    RcsData rcs = ModelManageController::getRcsData(targetId, originalAzimuth, originalElevation);
    rcsSpin->setValue(rcs.rcs_value);
}

void RcsEditDialog::onSaveRcs() {
    RcsData data;
    data.target_model_id = targetId;
    data.azimuth = azimuthSpin->value();
    data.elevation = elevationSpin->value();
    data.rcs_value = rcsSpin->value();
    
    bool success = false;
    if (isEditMode) {
        // 检查角度是否改变
        if (data.azimuth != originalAzimuth || data.elevation != originalElevation) {
            // 先删除旧数据
            ModelManageController::deleteRcsData(targetId, originalAzimuth, originalElevation);
        }
        success = ModelManageController::createRcsData(data);
    } else {
        success = ModelManageController::createRcsData(data);
    }
    
    if (success) {
        accept();
    } else {
        QMessageBox::warning(this, "错误", isEditMode ? "更新RCS数据失败" : "创建RCS数据失败");
    }
}