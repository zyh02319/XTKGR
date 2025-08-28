#include "JammerModelViewDialog.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QDialogButtonBox>

JammerModelViewDialog::JammerModelViewDialog(const JammerModel& model, QWidget *parent)
    : QDialog(parent) {
    setupUI(model);
}

void JammerModelViewDialog::setupUI(const JammerModel& model) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    QFormLayout *formLayout = new QFormLayout;

    formLayout->addRow("名称:", new QLabel(QString::fromStdString(model.name)));
    formLayout->addRow("干扰类型:", new QLabel(QString::fromStdString(model.jamming_type)));
    formLayout->addRow("功率:", new QLabel(QString("%1 W").arg(model.power)));
    formLayout->addRow("带宽:", new QLabel(QString("%1 MHz").arg(model.bandwidth)));
    formLayout->addRow("增益:", new QLabel(QString("%1 dB").arg(model.gain)));
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