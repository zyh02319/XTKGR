#include "TargetModelViewDialog.h"
#include <QVBoxLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QTextEdit>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QAbstractItemView>
#include <QStringList>
#include <QHeaderView>

TargetModelViewDialog::TargetModelViewDialog(const TargetModelWithRcs& model, QWidget *parent)
    : QDialog(parent), targetModel(model) {
    initUI();
    setWindowTitle("目标模型");
    setMinimumSize(500, 400);
}

void TargetModelViewDialog::initUI() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // === 目标模型信息 ===
    QGroupBox *infoGroup = new QGroupBox("目标模型信息");
    modelInfoText = new QTextEdit;
    modelInfoText->setReadOnly(true);
    
    QString info = QString("名称: %1\n"
                          "类型: %2\n"
                          "经度: %3\n"
                          "纬度: %4\n"
                          "高度: %5\n"
                          "航向: %6 °\n"
                          "飞行速度: %7 km/h")
                   .arg(QString::fromStdString(targetModel.targetModel.name))
                   .arg(QString::fromStdString(targetModel.targetModel.target_type))
                   .arg(targetModel.targetModel.longitude)
                   .arg(targetModel.targetModel.latitude)
                   .arg(targetModel.targetModel.altitude)
                   .arg(targetModel.targetModel.heading, 0, 'f', 2)
                   .arg(targetModel.targetModel.speed, 0, 'f', 2);
    
    modelInfoText->setPlainText(info);
    
    QVBoxLayout *infoLayout = new QVBoxLayout;
    infoLayout->addWidget(modelInfoText);
    infoGroup->setLayout(infoLayout);
    mainLayout->addWidget(infoGroup);
    
    // === RCS数据 ===
    QGroupBox *rcsGroup = new QGroupBox("RCS数据");
    rcsTable = new QTableWidget;
    rcsTable->setColumnCount(3);
    rcsTable->setHorizontalHeaderLabels(QStringList() << "方位角" << "俯仰角" << "RCS值");
    rcsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    rcsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    
    for (const auto& rcs : targetModel.rcsDataList) {
        int row = rcsTable->rowCount();
        rcsTable->insertRow(row);
        
        rcsTable->setItem(row, 0, new QTableWidgetItem(QString::number(rcs.azimuth)));
        rcsTable->setItem(row, 1, new QTableWidgetItem(QString::number(rcs.elevation)));
        rcsTable->setItem(row, 2, new QTableWidgetItem(QString::number(rcs.rcs_value)));
    }
    
    QVBoxLayout *rcsLayout = new QVBoxLayout;
    rcsLayout->addWidget(rcsTable);
    rcsGroup->setLayout(rcsLayout);
    mainLayout->addWidget(rcsGroup);
    
    setLayout(mainLayout);
}