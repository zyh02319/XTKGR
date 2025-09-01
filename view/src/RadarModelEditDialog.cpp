#include "RadarModelEditDialog.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QDialogButtonBox>

RadarModelEditDialog::RadarModelEditDialog(QWidget *parent)
    : QDialog(parent) {
    setupUI();
}

RadarModelEditDialog::RadarModelEditDialog(const RadarModel& model, QWidget *parent)
    : QDialog(parent), currentModel(model) {
    setupUI();
    // 填充数据
    nameEdit->setText(QString::fromStdString(model.name));
    wavelengthSpin->setValue(model.wavelength);
    powerSpin->setValue(model.power);
    bandwidthSpin->setValue(model.bandwidth);
    gainSpin->setValue(model.gain);
    // lossFactorSpin->setValue(model.loss_factor);
    longitudeSpin->setValue(model.longitude);
    latitudeSpin->setValue(model.latitude);
    altitudeSpin->setValue(model.altitude);
    headingSpin->setValue(model.heading);
    speedSpin->setValue(model.speed);
}

void RadarModelEditDialog::setupUI() {
    QVBoxLayout *layout = new QVBoxLayout(this);
    QFormLayout *formLayout = new QFormLayout;

    nameEdit = new QLineEdit(this);
    formLayout->addRow("名称:", nameEdit);

    wavelengthSpin = new QDoubleSpinBox(this);
    wavelengthSpin->setRange(0.001, 100); // 波长范围 (m)
    wavelengthSpin->setSuffix(" m");
    formLayout->addRow("波长:", wavelengthSpin);

    powerSpin = new QDoubleSpinBox(this);
    powerSpin->setRange(0, 10000);
    powerSpin->setSuffix(" KW");
    formLayout->addRow("功率:", powerSpin);

    bandwidthSpin = new QDoubleSpinBox(this);
    bandwidthSpin->setRange(0, 10000);
    bandwidthSpin->setSuffix(" MHz");
    formLayout->addRow("带宽:", bandwidthSpin);

    gainSpin = new QDoubleSpinBox(this);
    gainSpin->setRange(0, 100);
    gainSpin->setSuffix(" dB");
    formLayout->addRow("增益:", gainSpin);

    // lossFactorSpin = new QDoubleSpinBox(this);
    // lossFactorSpin->setRange(0, 100);
    // lossFactorSpin->setSuffix(" dB");
    // formLayout->addRow("损耗因子:", lossFactorSpin);

    longitudeSpin = new QDoubleSpinBox(this);
    longitudeSpin->setRange(-180, 180);
    longitudeSpin->setDecimals(6);
    formLayout->addRow("经度:", longitudeSpin);

    latitudeSpin = new QDoubleSpinBox(this);
    latitudeSpin->setRange(-90, 90);
    latitudeSpin->setDecimals(6);
    formLayout->addRow("纬度:", latitudeSpin);

    altitudeSpin = new QDoubleSpinBox(this);
    altitudeSpin->setRange(0, 10000);
    altitudeSpin->setSuffix(" m");
    formLayout->addRow("高度:", altitudeSpin);

    headingSpin = new QDoubleSpinBox(this);
    headingSpin->setRange(0, 360);
    headingSpin->setDecimals(2);
    headingSpin->setSuffix(" °");
    formLayout->addRow("航向:", headingSpin);

    speedSpin = new QDoubleSpinBox(this);
    speedSpin->setRange(0, 100000);
    speedSpin->setDecimals(2);
    speedSpin->setSuffix(" km/h");
    formLayout->addRow("飞行速度:", speedSpin);

    layout->addLayout(formLayout);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    layout->addWidget(buttonBox);
}

RadarModel RadarModelEditDialog::getRadarModel() const {
    RadarModel model;
    model.name = nameEdit->text().toStdString();
    model.wavelength = wavelengthSpin->value();
    model.power = powerSpin->value();
    model.bandwidth = bandwidthSpin->value();
    model.gain = gainSpin->value();
    // model.loss_factor = lossFactorSpin->value();
    model.longitude = longitudeSpin->value();
    model.latitude = latitudeSpin->value();
    model.altitude = altitudeSpin->value();
    model.heading = headingSpin->value();
    model.speed = speedSpin->value();
    model.id = currentModel.id; // 如果是编辑，需要设置id
    return model;
}