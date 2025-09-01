// PostMissionEvaluationView.h
#pragma once
#include <QWidget>
#include <QRadioButton>
#include <QPushButton>
#include <QTableWidget>  // 添加表格头文件
#include <QListWidget>   // 添加列表控件头文件
#include <QChartView>
#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QButtonGroup>
#include <QDialog>
#include <QList>         // 添加QList头文件

QT_CHARTS_USE_NAMESPACE

class PostMissionEvaluationView : public QWidget {
    Q_OBJECT
public:
    explicit PostMissionEvaluationView(QWidget *parent = nullptr);

private slots:
    void onImportData();
    void onConfirmImport();
    void onEvaluate();

private:
    QPushButton *btnImport;
    QPushButton *btnEvaluate;
    QRadioButton *rbSingle;
    QRadioButton *rbFormation;
    QTableWidget *resultTable;  // 改为QTableWidget
    QChartView *chartView;

    // 弹出选择数据的对话框
    QDialog *importDialog;
    QList<QListWidget*> categoryLists; // 三类（干扰机、目标机、探测模型）
};