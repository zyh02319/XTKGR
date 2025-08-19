#pragma once
#include <QWidget>
#include <QButtonGroup>
#include <QRadioButton>
#include <QPushButton>
#include <QTableWidget>
#include <QLineEdit>
#include <QScrollArea>  // 添加滚动区域支持


class ModelManagerView : public QWidget {
    Q_OBJECT
public:
    explicit ModelManagerView(QWidget *parent = nullptr);

private slots:
    void onModelTypeChanged(int id);
    void onCreateModel();
    void onEditModel(int row);
    void onDeleteModel(int row);
    void onViewModel(int row);
    void onSearch();  // 添加搜索功能槽

private:
    QButtonGroup *modelTypeGroup;
    QRadioButton *interferenceRadio;
    QRadioButton *detectionRadio;
    QRadioButton *targetRadio;
    QPushButton *createButton;
    QTableWidget *modelTable;
    QLineEdit *searchEdit;  // 添加搜索框
    QPushButton *searchButton;  // 添加搜索按钮
    QScrollArea *scrollArea;  // 添加滚动区域
    
    void loadModels();
    void setupTable();
    int currentModelType;
};