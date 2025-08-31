// DetectionPerformanceView.h
#pragma once
#include <QWidget>
#include <QTabWidget>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <vector>
#include "SingleEvaluationController.h"
#include "FormationEvaluationController.h" // 添加编队评估控制器
// #include "GeoUtils.h"

class ModelSelectionDialog;

class DetectionPerformanceView : public QWidget {
	Q_OBJECT
public:
	explicit DetectionPerformanceView(QWidget *parent = nullptr);
	~DetectionPerformanceView();
	 // 添加距离计算函数
	static double calculateSpatialDistance(
		double lon1, double lat1, double alt1, 
		double lon2, double lat2, double alt2);

private slots:
	void onConditionChanged(int index);
	void onSelectRadar();
	void onSelectJammer();
	void onSelectTarget();
	void onEvaluate();
	void showRadarDetails();
	void showJammerDetails();
	void showTargetDetails();
	
	// 编队评估槽函数
	void onFormationConditionChanged(int index);
	void onSelectFormationRadar();
	void onAddFormationRadar();
	void onDeleteFormationRadar();
	void onSelectFormationJammer();
	void onSelectFormationTarget();
	void onFormationEvaluate();
	void showFormationRadarDetails();
	void showFormationJammerDetails();
	void showFormationTargetDetails();

private:
	void setupUI();
	void setupSingleEvaluationUI(); // 单独的单机评估UI设置
	void setupFormationUI();        // 单独的编队评估UI设置
	void updateModelDisplay();
	void updateFormationModelDisplay(); // 编队模型显示更新

	QTabWidget *tabWidget;
	QWidget *singleEvaluationTab;
	QWidget *formationEvaluationTab; // 编队评估标签页
	
	// 单机评估控件
	QComboBox *conditionComboBox;
	QPushButton *selectRadarButton;
	QPushButton *selectJammerButton;
	QPushButton *selectTargetButton;
	QPushButton *evaluateButton;
	QLabel *radarLabel;
	QLabel *jammerLabel;
	QLabel *targetLabel;
	QLabel *rcsLabel;
	QLabel *distanceValueLabel;  
	QLabel *trackValueLabel;     
	QLabel *reasonValueLabel;  
	QLabel *distanceValue;  
	QLabel *trackValue;     
	QLabel *reasonValue;    
	
	// 编队评估控件
	// QComboBox *formationAlgorithmComboBox;
	QComboBox *formationConditionComboBox;
	QPushButton *selectFormationRadarButton;
	QPushButton *addFormationRadarButton;
	QPushButton *deleteFormationRadarButton;
	QPushButton *selectFormationJammerButton;
	QPushButton *selectFormationTargetButton;
	QPushButton *formationEvaluateButton;
	QLabel *formationRadarLabel;
	QLabel *formationJammerLabel;
	QLabel *formationTargetLabel;
	QLabel *formationRcsLabel;
	QLabel *formationDistanceValueLabel;
	QLabel *formationTrackValueLabel;
	QLabel *formationReasonValueLabel;
	QLabel *formationDistanceValue;
	QLabel *formationTrackValue;
	QLabel *formationReasonValue;
	
	// 当前选中的模型 - 使用指针替代optional
	RadarModel* currentRadar = nullptr;
	JammerModel* currentJammer = nullptr;
	TargetModel* currentTarget = nullptr;
	RcsData* currentRcs = nullptr;
	
	// 编队评估模型（多雷达）
	std::vector<RadarModel*> currentFormationRadars;
	JammerModel* currentFormationJammer = nullptr;
	TargetModel* currentFormationTarget = nullptr;
	RcsData* currentFormationRcs = nullptr;
	
	// 对话框
	ModelSelectionDialog *radarDialog;
	ModelSelectionDialog *jammerDialog;
	ModelSelectionDialog *targetDialog;
	ModelSelectionDialog *radarDialogForFormationRadar = nullptr; // 雷达模型专用对话框
	ModelSelectionDialog *jammerDialogForFormation = nullptr; // 编队干扰模型专用对话框
	ModelSelectionDialog *targetDialogForFormationTarget = nullptr; // 编队目标模型专用对话框

	// 状态标志：用于区分选择/增加雷达
	bool isAddingFormationRadar = false;
	
};