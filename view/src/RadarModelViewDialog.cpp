#include "RadarModelViewDialog.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QDialogButtonBox>

RadarModelViewDialog::RadarModelViewDialog(const RadarModel& model, QWidget *parent)
    : QDialog(parent) {
    setupUI(model);
}

void RadarModelViewDialog::setupUI(const RadarModel& model) {
    setWindowTitle("探测模型");
    QVBoxLayout *layout = new QVBoxLayout(this);
    QFormLayout *formLayout = new QFormLayout;

    formLayout->addRow("名称:", new QLabel(QString::fromStdString(model.name)));
    formLayout->addRow("波长:", new QLabel(QString("%1 m").arg(model.wavelength)));
    formLayout->addRow("功率:", new QLabel(QString("%1 KW").arg(model.power)));
    formLayout->addRow("带宽:", new QLabel(QString("%1 MHz").arg(model.bandwidth)));
    formLayout->addRow("增益:", new QLabel(QString("%1 dB").arg(model.gain)));
    // formLayout->addRow("损耗因子:", new QLabel(QString("%1 dB").arg(model.loss_factor)));
    formLayout->addRow("经度:", new QLabel(QString::number(model.longitude, 'f', 6)));
    formLayout->addRow("纬度:", new QLabel(QString::number(model.latitude, 'f', 6)));
    formLayout->addRow("高度:", new QLabel(QString("%1 m").arg(model.altitude)));
    formLayout->addRow("航向:", new QLabel(QString("%1 °").arg(model.heading)));
    formLayout->addRow("飞行速度:", new QLabel(QString("%1 km/h").arg(model.speed)));

    layout->addLayout(formLayout);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok, this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    layout->addWidget(buttonBox);
}