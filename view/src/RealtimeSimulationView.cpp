#include "RealtimeSimulationView.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>
#include <QFrame>
#include <QPainter>
#include <QPaintEvent>
#include <QGroupBox>

// ===== 模拟实况画布 =====
class SimulationCanvas : public QFrame {
public:
    SimulationCanvas(QWidget *parent = nullptr) : QFrame(parent) {
        setStyleSheet("background-color:#eef6fa; border:1px solid #aaa;"); 
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        QFrame::paintEvent(event);
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        // === 预警机 E-01 ===
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(100, 149, 237));
        painter.drawEllipse(QPoint(120,120), 10,10);
        painter.setPen(QPen(QColor(100,149,237,80), 1));
        painter.setBrush(Qt::NoBrush);
        painter.drawEllipse(QPoint(120,120), 70,70);
        painter.setPen(Qt::black);
        painter.drawText(135,115,"E-01");

        // === 预警机 E-02 ===
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(65,105,225));
        painter.drawEllipse(QPoint(300,150), 10,10);
        painter.setPen(QPen(QColor(65,105,225,80), 1));
        painter.setBrush(Qt::NoBrush);
        painter.drawEllipse(QPoint(300,150), 70,70);
        painter.setPen(Qt::black);
        painter.drawText(315,145,"E-02");

        // === 干扰机 J-01 ===
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(186,85,211));
        painter.drawEllipse(QPoint(220,250), 10,10);
        // 删除了干扰机的圆
        painter.setPen(Qt::black);
        painter.drawText(235,245,"J-01");

        // === 目标机 T-01 ===
        painter.setBrush(Qt::red);
        QPoint target[3] = { QPoint(200,80), QPoint(190,100), QPoint(210,100) };
        painter.drawPolygon(target,3);
        painter.setPen(Qt::black);
        painter.drawText(215,95,"T-01");

        // 删除了右上角图例说明
    }
};

// ===== 主界面 =====
RealtimeSimulationView::RealtimeSimulationView(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
}

static QWidget* createDataBlock(const QString &title, const QStringList &lines) {
    auto box = new QGroupBox(title);
    box->setStyleSheet(
        "QGroupBox {"
        "  font-weight: bold;"
        "  border: 1px solid #ccc;"  // 简单的灰色边框
        "  margin-top: 1ex;"
        "  background-color: transparent;"  // 透明背景
        "}"
        "QGroupBox::title {"
        "  subcontrol-origin: margin;"
        "  subcontrol-position: top center;"
        "  padding: 0 5px;"
        "}"
    );
    
    auto vbox = new QVBoxLayout(box);
    for (auto &line : lines) {
        auto lbl = new QLabel(line);
        lbl->setStyleSheet("font-size:14px; padding:2px;");
        vbox->addWidget(lbl);
    }
    return box;
}

void RealtimeSimulationView::setupUI() {
    // 顶部按钮栏
    auto topLayout = new QHBoxLayout;
    auto btnStart = new QPushButton("开始仿真");
    auto btnPause = new QPushButton("暂停");
    auto btnStop = new QPushButton("停止");  // 修改为停止按钮
    topLayout->addWidget(btnStart);
    topLayout->addWidget(btnPause);
    topLayout->addWidget(btnStop);
    topLayout->addStretch();
    auto lblData = new QLabel("● 数据接受中");  // 修改文本
    lblData->setStyleSheet("color:green;font-weight:bold;");
    topLayout->addWidget(lblData);

    // 左侧实时数据（用 QGroupBox + Label 展示）
    auto leftLayout = new QVBoxLayout;
    
    // 添加"实时数据"标题
    auto realtimeDataLabel = new QLabel("实时数据");
    realtimeDataLabel->setStyleSheet("font-size:16px; font-weight:bold; margin:10px 0;");
    leftLayout->addWidget(realtimeDataLabel);
    
    // 所有数据框使用简单的边框，没有颜色
    leftLayout->addWidget(createDataBlock("预警机 E-01", {
        "经度: 120.5°    纬度: 36.2°",  // 添加了度符号
        "航向: 90°       速度: 850 km/h",
        "雷达扇区: 前方120°",
        "抗干扰: 开启"
    }));
    
    leftLayout->addWidget(createDataBlock("预警机 E-02", {
        "经度: 121.3°    纬度: 35.9°",  // 添加了度符号
        "航向: 75°       速度: 820 km/h",
        "雷达扇区: 前方90°",
        "抗干扰: 关闭"
    }));
    
    leftLayout->addWidget(createDataBlock("干扰机 J-01", {
        "经度: 122.0°    纬度: 36.0°",  // 添加了度符号
        "航向: 110°      速度: 750 km/h",
        "干扰带宽: 50 MHz",
        "功率: 2 kW"
    }));
    
    leftLayout->addWidget(createDataBlock("目标机 T-01", {
        "经度: 121.7°    纬度: 36.4°",  // 添加了度符号
        "航向: 95°       速度: 900 km/h"
    }));
    
    leftLayout->addStretch();

    // 中间模拟实况
    auto simCanvas = new SimulationCanvas;

    // 右侧实时评估指标（字体更大、更突出）
    auto rightLayout = new QVBoxLayout;
    
    // 添加"实时评估指标"标题
    auto evalLabel = new QLabel("实时评估指标");
    evalLabel->setStyleSheet("font-size:16px; font-weight:bold; margin:10px 0;");
    rightLayout->addWidget(evalLabel);
    
    auto lblMaxDist = new QLabel("最远探测距离: 318 km");
    lblMaxDist->setStyleSheet("font-size:18px; font-weight:bold; color:#003366;");

    auto lblCont = new QLabel("目标航迹连续性:");
    lblCont->setStyleSheet("font-size:16px; font-weight:bold;");
    auto progress = new QProgressBar;
    progress->setValue(92);
    progress->setStyleSheet("height:20px; font-size:14px;");

    auto lblBreak = new QLabel("探测中断次数: 2");
    lblBreak->setStyleSheet("font-size:16px; font-weight:bold; color:#660000;");
    auto lblReason = new QLabel("原因: 受欺骗干扰");
    lblReason->setStyleSheet("font-size:14px;");

    rightLayout->addWidget(lblMaxDist);
    rightLayout->addSpacing(10);
    rightLayout->addWidget(lblCont);
    rightLayout->addWidget(progress);
    rightLayout->addSpacing(10);
    rightLayout->addWidget(lblBreak);
    rightLayout->addWidget(lblReason);
    rightLayout->addStretch();

    // 主布局
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(topLayout);

    auto contentLayout = new QHBoxLayout;
    contentLayout->addLayout(leftLayout,3);
    contentLayout->addWidget(simCanvas,5);
    contentLayout->addLayout(rightLayout,2);

    mainLayout->addLayout(contentLayout);
}