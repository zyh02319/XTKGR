#pragma once
#include <QDialog>

class QDoubleSpinBox;

class RcsEditDialog : public QDialog {
    Q_OBJECT
public:
    // 修复参数列表
    explicit RcsEditDialog(int targetId, QWidget *parent = nullptr);
    explicit RcsEditDialog(int targetId, double azimuth, double elevation, QWidget *parent = nullptr);
    
private slots:
    void onSaveRcs();
    
private:
    void initUI();
    void loadData();
    
    int targetId;
    double originalAzimuth;
    double originalElevation;
    bool isEditMode;
    
    QDoubleSpinBox *azimuthSpin;
    QDoubleSpinBox *elevationSpin;
    QDoubleSpinBox *rcsSpin;
};