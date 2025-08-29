// PostMissionEvaluationView.cpp
#include "PostMissionEvaluationView.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QDialogButtonBox>
#include <QListWidget>
#include <QCheckBox>
#include <QMessageBox>
#include <QtCharts/QChart>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QHeaderView>  // 添加头文件以设置表格属性
#include <QTableWidget>  // 添加表格头文件

PostMissionEvaluationView::PostMissionEvaluationView(QWidget *parent)
    : QWidget(parent)
{
    // 上半部分控件
    btnImport = new QPushButton("导入数据");
    btnEvaluate = new QPushButton("评估");
    rbSingle = new QRadioButton("单机评估");
    rbFormation = new QRadioButton("编队评估");
    rbSingle->setChecked(true);

    QButtonGroup *group = new QButtonGroup(this);
    group->addButton(rbSingle);
    group->addButton(rbFormation);

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(btnImport);
    topLayout->addWidget(btnEvaluate);
    topLayout->addWidget(rbSingle);
    topLayout->addWidget(rbFormation);
    topLayout->addStretch();

    // 下半部分：左边表格 + 右边柱状图
    resultTable = new QTableWidget;
    resultTable->setColumnCount(3);  // 三列：指标类别、指标名称、得分
    resultTable->setHorizontalHeaderLabels(QStringList() << "指标类别" << "指标名称" << "得分");
    resultTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    resultTable->verticalHeader()->setVisible(false);
    resultTable->setShowGrid(true);  // 显示网格线
    resultTable->setStyleSheet("QTableWidget { gridline-color: #d0d0d0; }");  // 设置网格线颜色
    
    chartView = new QChartView(new QChart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addWidget(resultTable, 1);
    bottomLayout->addWidget(chartView, 2);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(bottomLayout);

    connect(btnImport, &QPushButton::clicked, this, &PostMissionEvaluationView::onImportData);
    connect(btnEvaluate, &QPushButton::clicked, this, &PostMissionEvaluationView::onEvaluate);
}

void PostMissionEvaluationView::onImportData()
{
    importDialog = new QDialog(this);
    importDialog->setWindowTitle("选择数据");

    QVBoxLayout *dlgLayout = new QVBoxLayout(importDialog);

    QStringList categories = {"干扰机", "目标机", "雷达模型"};
    categoryLists.clear();

    for (const QString &cat : categories) {
        QGroupBox *box = new QGroupBox(cat);
        QVBoxLayout *boxLayout = new QVBoxLayout;
        QListWidget *list = new QListWidget;
        for (int i = 1; i <= 8; i++) {
            QListWidgetItem *item = new QListWidgetItem(cat + QString::number(i));
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
            item->setCheckState(Qt::Unchecked);
            list->addItem(item);
        }
        categoryLists.append(list);
        boxLayout->addWidget(list);
        box->setLayout(boxLayout);
        dlgLayout->addWidget(box);
    }

    QPushButton *btnConfirm = new QPushButton("确认");
    connect(btnConfirm, &QPushButton::clicked, this, &PostMissionEvaluationView::onConfirmImport);
    dlgLayout->addWidget(btnConfirm);

    importDialog->exec();
}

void PostMissionEvaluationView::onConfirmImport()
{
    // 简单校验
    if (rbSingle->isChecked()) {
        // 单机：每个分类只能选 1 个
        for (QListWidget *list : categoryLists) {
            int cnt = 0;
            for (int i = 0; i < list->count(); i++) {
                if (list->item(i)->checkState() == Qt::Checked)
                    cnt++;
            }
            if (cnt != 1) {
                QMessageBox::warning(importDialog, "错误", "单机评估下每类必须选择一个");
                return;
            }
        }
    } else {
        // 编队：干扰机和目标机 1 个，雷达模型至少 1 个
        for (int c = 0; c < categoryLists.size(); c++) {
            QListWidget *list = categoryLists[c];
            int cnt = 0;
            for (int i = 0; i < list->count(); i++) {
                if (list->item(i)->checkState() == Qt::Checked)
                    cnt++;
            }
            if (c < 2 && cnt != 1) {
                QMessageBox::warning(importDialog, "错误", "干扰机和目标机必须各选一个");
                return;
            }
            if (c == 2 && cnt < 1) {
                QMessageBox::warning(importDialog, "错误", "编队评估下雷达模型至少选一个");
                return;
            }
        }
    }

    importDialog->accept();
}

void PostMissionEvaluationView::onEvaluate()
{
    // 清空表格
    resultTable->setRowCount(0);
    
    // 根据评估类型填充不同的数据
    if (rbSingle->isChecked()) {
        // 单机评估数据
        QStringList singleData = {
            "探测距离", "最远发现距离", "85",
            "探测距离", "最远稳定跟踪距离", "80",
            "探测精度", "位置精度", "77",
            "探测精度", "方位精度", "75",
            "探测精度", "高度精度", "75",
            "探测精度", "距离精度", "85",
            "目标航迹连续性", "时间掌握率", "88",
            "目标航迹连续性", "暂消时长", "85",
            "分辨力", "方位分辨力", "84",
            "分辨力", "距离分辨力", "90"
        };
        
        // 填充表格
        for (int i = 0; i < singleData.size(); i += 3) {
            int row = resultTable->rowCount();
            resultTable->insertRow(row);
            resultTable->setItem(row, 0, new QTableWidgetItem(singleData[i]));
            resultTable->setItem(row, 1, new QTableWidgetItem(singleData[i+1]));
            resultTable->setItem(row, 2, new QTableWidgetItem(singleData[i+2]));
        }
        
        // 单机评估柱状图数据
        QChart *chart = new QChart;
        chart->setTitle("单机评估结果对比");

        QBarSet *realSet = new QBarSet("真实结果");
        QBarSet *simSet = new QBarSet("仿真结果");

        *realSet << 85 << 77 << 88 << 84;
        *simSet  << 80 << 75 << 85 << 90;

        QBarSeries *series = new QBarSeries;
        series->append(realSet);
        series->append(simSet);
        chart->addSeries(series);

        QStringList categories;
        categories << "探测距离" << "探测精度" << "目标航迹连续性" << "分辨力";
        QBarCategoryAxis *axisX = new QBarCategoryAxis;
        axisX->append(categories);
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        QValueAxis *axisY = new QValueAxis;
        axisY->setRange(0, 100);
        axisY->setTitleText("百分比");
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);

        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);

        chartView->setChart(chart);
    } else {
        // 编队评估数据 (使用不同的示例数据)
        QStringList formationData = {
            "探测距离", "最远发现距离", "92",
            "探测距离", "最远稳定跟踪距离", "87",
            "探测精度", "位置精度", "82",
            "探测精度", "方位精度", "80",
            "探测精度", "高度精度", "78",
            "探测精度", "距离精度", "88",
            "目标航迹连续性", "时间掌握率", "90",
            "目标航迹连续性", "暂消时长", "87",
            "分辨力", "方位分辨力", "86",
            "分辨力", "距离分辨力", "93"
        };
        
        // 填充表格
        for (int i = 0; i < formationData.size(); i += 3) {
            int row = resultTable->rowCount();
            resultTable->insertRow(row);
            resultTable->setItem(row, 0, new QTableWidgetItem(formationData[i]));
            resultTable->setItem(row, 1, new QTableWidgetItem(formationData[i+1]));
            resultTable->setItem(row, 2, new QTableWidgetItem(formationData[i+2]));
        }
        
        // 编队评估柱状图数据
        QChart *chart = new QChart;
        chart->setTitle("编队评估结果对比");

        QBarSet *realSet = new QBarSet("真实结果");
        QBarSet *simSet = new QBarSet("仿真结果");  // 修复这里：使用QBarSet而不是QTableWidgetItem

        *realSet << 92 << 82 << 90 << 86;
        *simSet  << 87 << 80 << 87 << 93;

        QBarSeries *series = new QBarSeries;
        series->append(realSet);
        series->append(simSet);
        chart->addSeries(series);

        QStringList categories;
        categories << "探测距离" << "探测精度" << "目标航迹连续性" << "分辨力";
        QBarCategoryAxis *axisX = new QBarCategoryAxis;
        axisX->append(categories);
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        QValueAxis *axisY = new QValueAxis;
        axisY->setRange(0, 100);
        axisY->setTitleText("百分比");
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);

        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);

        chartView->setChart(chart);
    }
    
    // 合并相同类别的单元格，使其看起来像图片中的表格
    for (int row = 0; row < resultTable->rowCount(); row++) {
        QString currentCategory = resultTable->item(row, 0)->text();
        int startRow = row;
        
        // 查找相同类别的连续行
        while (row + 1 < resultTable->rowCount() && 
               resultTable->item(row + 1, 0)->text() == currentCategory) {
            row++;
        }
        
        // 合并单元格
        if (row > startRow) {
            resultTable->setSpan(startRow, 0, row - startRow + 1, 1);
        }
    }
}