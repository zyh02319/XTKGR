#include "../ModelManagerView.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QLabel>
#include <QScrollBar>
#include "ModelManageController.h"  // 包含控制器头文件
#include "JammerModelEditDialog.h"  // 包含编辑对话框
#include "JammerModelViewDialog.h"  // 包含查看对话框
#include "RadarModelEditDialog.h" // 添加探测模型编辑对话框
#include "RadarModelViewDialog.h" // 添加探测模型查看对话框
#include "TargetModelEditDialog.h"  // 目标模型编辑对话框
#include "TargetModelViewDialog.h"  // 目标模型查看对话框

ModelManagerView::ModelManagerView(QWidget *parent)
    : QWidget(parent), currentModelType(0)
{
    // 创建主滚动区域
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    
    // 创建容器Widget
    QWidget *container = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(container);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    // === 搜索区域 ===
    QHBoxLayout *searchLayout = new QHBoxLayout();
    searchLayout->addWidget(new QLabel("搜索模型:"));
    
    searchEdit = new QLineEdit(this);
    searchEdit->setPlaceholderText("请输入模型名称");
    searchEdit->setClearButtonEnabled(true);
    searchLayout->addWidget(searchEdit, 1);  // 设置拉伸因子为1
    
    searchButton = new QPushButton("搜索", this);
    searchLayout->addWidget(searchButton);
    
    mainLayout->addLayout(searchLayout);

    // === 模型类型选择 ===
    QHBoxLayout *typeLayout = new QHBoxLayout;
    modelTypeGroup = new QButtonGroup(this);
    interferenceRadio = new QRadioButton("干扰模型", this);
    detectionRadio = new QRadioButton("探测模型", this);
    targetRadio = new QRadioButton("目标模型", this);
    
    modelTypeGroup->addButton(interferenceRadio, 0);
    modelTypeGroup->addButton(detectionRadio, 1);
    modelTypeGroup->addButton(targetRadio, 2);
    
    interferenceRadio->setChecked(true);
    typeLayout->addWidget(interferenceRadio);
    typeLayout->addWidget(detectionRadio);
    typeLayout->addWidget(targetRadio);
    
    mainLayout->addLayout(typeLayout);

    // === 新建按钮 ===
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    createButton = new QPushButton("新建模型", this);
    buttonLayout->addWidget(createButton);
    buttonLayout->addStretch();  // 添加弹簧使按钮靠左
    mainLayout->addLayout(buttonLayout);

    // === 模型列表 ===
    modelTable = new QTableWidget(this);
    modelTable->setColumnCount(4);
    QStringList headers;
    headers << "模型名称" << "编辑" << "删除" << "查看";
    modelTable->setHorizontalHeaderLabels(headers);
    modelTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch); // 仅名称列拉伸
    modelTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    modelTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    modelTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    modelTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    modelTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn); // 确保表格有自己的滚动条
    mainLayout->addWidget(modelTable);

    // 设置容器到滚动区域
    container->setLayout(mainLayout);
    scrollArea->setWidget(container);
    
    // 设置主布局
    QVBoxLayout *outerLayout = new QVBoxLayout(this);
    outerLayout->addWidget(scrollArea);
    outerLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(outerLayout);

    // 连接信号
    connect(modelTypeGroup, QOverload<int>::of(&QButtonGroup::buttonClicked), 
            this, &ModelManagerView::onModelTypeChanged);
    connect(createButton, &QPushButton::clicked, this, &ModelManagerView::onCreateModel);
    connect(searchButton, &QPushButton::clicked, this, &ModelManagerView::onSearch);
    connect(searchEdit, &QLineEdit::returnPressed, this, &ModelManagerView::onSearch);

    loadModels();
}

void ModelManagerView::onModelTypeChanged(int id) {
    currentModelType = id;
    loadModels();
}

// 新增搜索功能
void ModelManagerView::onSearch() {
    loadModels();
}

void ModelManagerView::onCreateModel() {
    if (currentModelType == 0) { // 干扰机模型
        JammerModelEditDialog dialog;
        if (dialog.exec() == QDialog::Accepted) {
            JammerModel model = dialog.getJammerModel();
            if (ModelManageController::createJammerModel(model)) {
                QMessageBox::information(this, "成功", "干扰机模型创建成功");
                loadModels(); // 刷新
            } else {
                QMessageBox::warning(this, "错误", "创建干扰机模型失败");
            }
        }
    } else if (currentModelType == 1) { // 探测模型
        RadarModelEditDialog dialog;
        if (dialog.exec() == QDialog::Accepted) {
            RadarModel model = dialog.getRadarModel();
            if (ModelManageController::createRadarModel(model)) {
                QMessageBox::information(this, "成功", "探测模型创建成功");
                loadModels(); // 刷新
            } else {
                QMessageBox::warning(this, "错误", "创建探测模型失败");
            }
        }
    }  else if (currentModelType == 2) { // 目标模型
        TargetModelEditDialog dialog;
        if (dialog.exec() == QDialog::Accepted) {
            // 不再调用 createTargetModel 方法
            loadModels(); // 只需要刷新
        }
        // TargetModelEditDialog dialog;
        // if (dialog.exec() == QDialog::Accepted) {
        //     TargetModel model = dialog.getTargetModel();
        //     if (ModelManageController::createTargetModel(model)) {
        //         QMessageBox::information(this, "成功", "目标模型创建成功");
        //         loadModels(); // 刷新
        //     } else {
        //         QMessageBox::warning(this, "错误", "创建目标模型失败");
        //     }
        // }
    }
}

void ModelManagerView::onEditModel(int row) {
    // 这个函数现在在loadModels中直接处理了
    Q_UNUSED(row);
}

void ModelManagerView::onDeleteModel(int row) {
    // 这个函数现在在loadModels中直接处理了
    Q_UNUSED(row);
}

void ModelManagerView::onViewModel(int row) {
    // 这个函数现在在loadModels中直接处理了
    Q_UNUSED(row);
}

void ModelManagerView::loadModels() {
    // 获取搜索关键词
    QString keyword = searchEdit->text().trimmed();
    
    // 清空表格
    modelTable->setRowCount(0);
    
    if (currentModelType == 0) { // 干扰机模型
        std::vector<std::pair<int, std::string>> models;
        
        if (keyword.isEmpty()) {
            models = ModelManageController::getAllJammerNamesAndIds();
        } else {
            models = ModelManageController::searchJammerModelsByName(keyword.toStdString());
        }
        
        if (models.empty()) {
            modelTable->setRowCount(1);
            modelTable->setItem(0, 0, new QTableWidgetItem("没有找到匹配的干扰机模型"));
            modelTable->setSpan(0, 0, 1, 4);
            modelTable->item(0, 0)->setTextAlignment(Qt::AlignCenter);
            return;
        }
        
        for (const auto& model : models) {
            int row = modelTable->rowCount();
            modelTable->insertRow(row);
            
            // 确保正确设置模型名称
            modelTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(model.second)));
            
            QPushButton *editBtn = new QPushButton("编辑");
            QPushButton *delBtn = new QPushButton("删除");
            QPushButton *viewBtn = new QPushButton("查看");
            
            modelTable->setCellWidget(row, 1, editBtn);
            modelTable->setCellWidget(row, 2, delBtn);
            modelTable->setCellWidget(row, 3, viewBtn);
            
            // 使用智能指针确保变量生命周期
            QSharedPointer<int> modelIdPtr(new int(model.first));
            
            connect(editBtn, &QPushButton::clicked, [this, modelIdPtr]() {
                JammerModel fullModel = ModelManageController::getJammerModelById(*modelIdPtr);
                JammerModelEditDialog dialog(fullModel);
                if (dialog.exec() == QDialog::Accepted) {
                    JammerModel updatedModel = dialog.getJammerModel();
                    if (ModelManageController::updateJammerModel(updatedModel)) {
                        QMessageBox::information(this, "成功", "干扰机模型更新成功");
                        loadModels(); // 更新视图
                    } else {
                        QMessageBox::warning(this, "错误", "更新干扰机模型失败");
                    }
                }
            });
            
            connect(delBtn, &QPushButton::clicked, [this, modelIdPtr]() {
                if (QMessageBox::question(this, "确认", "确定要删除该干扰机模型吗？") == QMessageBox::Yes) {
                    if (ModelManageController::deleteJammerModel(*modelIdPtr)) {
                        QMessageBox::information(this, "成功", "干扰机模型删除成功");
                        loadModels();
                    } else {
                        QMessageBox::warning(this, "错误", "删除干扰机模型失败");
                    }
                }
            });
            
            connect(viewBtn, &QPushButton::clicked, [this, modelIdPtr]() {
                JammerModel fullModel = ModelManageController::getJammerModelById(*modelIdPtr);
                JammerModelViewDialog dialog(fullModel);
                dialog.exec();
            });
        }
    } else if (currentModelType == 1) { // 探测模型
        std::vector<std::pair<int, std::string>> models;
        
        if (keyword.isEmpty()) {
            models = ModelManageController::getAllRadarNamesAndIds();
        } else {
            models = ModelManageController::searchRadarModelsByName(keyword.toStdString());
        }
        
        if (models.empty()) {
            modelTable->setRowCount(1);
            modelTable->setItem(0, 0, new QTableWidgetItem("没有找到匹配的探测模型"));
            modelTable->setSpan(0, 0, 1, 4);
            modelTable->item(0, 0)->setTextAlignment(Qt::AlignCenter);
            return;
        }
        
        for (const auto& model : models) {
            int row = modelTable->rowCount();
            modelTable->insertRow(row);
            modelTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(model.second)));
            
            QPushButton *editBtn = new QPushButton("编辑");
            QPushButton *delBtn = new QPushButton("删除");
            QPushButton *viewBtn = new QPushButton("查看");
            
            modelTable->setCellWidget(row, 1, editBtn);
            modelTable->setCellWidget(row, 2, delBtn);
            modelTable->setCellWidget(row, 3, viewBtn);
            
            // 使用智能指针确保变量生命周期
            QSharedPointer<int> modelIdPtr(new int(model.first));
            
            connect(editBtn, &QPushButton::clicked, [this, modelIdPtr]() {
                RadarModel fullModel = ModelManageController::getRadarModelById(*modelIdPtr);
                RadarModelEditDialog dialog(fullModel);
                if (dialog.exec() == QDialog::Accepted) {
                    RadarModel updatedModel = dialog.getRadarModel();
                    if (ModelManageController::updateRadarModel(updatedModel)) {
                        QMessageBox::information(this, "成功", "探测模型更新成功");
                        loadModels(); // 更新视图
                    } else {
                        QMessageBox::warning(this, "错误", "更新探测模型失败");
                    }
                }
            });
            
            connect(delBtn, &QPushButton::clicked, [this, modelIdPtr]() {
                if (QMessageBox::question(this, "确认", "确定要删除该探测模型吗？") == QMessageBox::Yes) {
                    if (ModelManageController::deleteRadarModel(*modelIdPtr)) {
                        QMessageBox::information(this, "成功", "探测模型删除成功");
                        loadModels();
                    } else {
                        QMessageBox::warning(this, "错误", "删除探测模型失败");
                    }
                }
            });
            
            connect(viewBtn, &QPushButton::clicked, [this, modelIdPtr]() {
                RadarModel fullModel = ModelManageController::getRadarModelById(*modelIdPtr);
                RadarModelViewDialog dialog(fullModel);
                dialog.exec();
            });
        }
    } else if (currentModelType == 2) { // 目标模型
        std::vector<std::pair<int, std::string>> models;
        
        if (keyword.isEmpty()) {
            models = ModelManageController::getAllTargetNamesAndIds();
        } else {
            models = ModelManageController::searchTargetModelsByName(keyword.toStdString());
        }
        
        if (models.empty()) {
            modelTable->setRowCount(1);
            modelTable->setItem(0, 0, new QTableWidgetItem("没有找到匹配的目标模型"));
            modelTable->setSpan(0, 0, 1, 4);
            modelTable->item(0, 0)->setTextAlignment(Qt::AlignCenter);
            return;
        }
        
        for (const auto& model : models) {
            int row = modelTable->rowCount();
            modelTable->insertRow(row);
            modelTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(model.second)));
            
            QPushButton *editBtn = new QPushButton("编辑");
            QPushButton *delBtn = new QPushButton("删除");
            QPushButton *viewBtn = new QPushButton("查看");
            
            modelTable->setCellWidget(row, 1, editBtn);
            modelTable->setCellWidget(row, 2, delBtn);
            modelTable->setCellWidget(row, 3, viewBtn);
            
            // 使用智能指针确保变量生命周期
            QSharedPointer<int> modelIdPtr(new int(model.first));
            
            // 编辑按钮
            connect(editBtn, &QPushButton::clicked, [this, modelIdPtr]() {
                TargetModelEditDialog dialog(*modelIdPtr);
                if (dialog.exec() == QDialog::Accepted) {
                    loadModels(); // 更新视图
                }
            });
            
            // 删除按钮
            connect(delBtn, &QPushButton::clicked, [this, modelIdPtr]() {
                if (QMessageBox::question(this, "确认", "确定要删除该目标模型及其所有RCS数据吗？") == QMessageBox::Yes) {
                    if (ModelManageController::deleteTargetModel(*modelIdPtr)) {
                        QMessageBox::information(this, "成功", "目标模型删除成功");
                        loadModels();
                    } else {
                        QMessageBox::warning(this, "错误", "删除目标模型失败");
                    }
                }
            });
            
            // 查看按钮
            connect(viewBtn, &QPushButton::clicked, [this, modelIdPtr]() {
                TargetModelWithRcs fullModel = ModelManageController::getTargetModelWithRcsById(*modelIdPtr);
                TargetModelViewDialog dialog(fullModel);
                dialog.exec();
            });
        }
    }
}