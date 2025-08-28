#pragma once
#include <QDialog>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include "RadarModelDAO.h"

class RadarModelEditDialog : public QDialog {
    Q_OBJECT
public:
    explicit RadarModelEditDialog(QWidget *parent = nullptr);
    RadarModelEditDialog(const RadarModel& model, QWidget *parent = nullptr);
    RadarModel getRadarModel() const;

private:
    void setupUI();
    QLineEdit *nameEdit;
    QDoubleSpinBox *wavelengthSpin;
    QDoubleSpinBox *powerSpin;
    QDoubleSpinBox *bandwidthSpin;
    QDoubleSpinBox *gainSpin;
    QDoubleSpinBox *lossFactorSpin;
    QDoubleSpinBox *longitudeSpin;
    QDoubleSpinBox *latitudeSpin;
    QDoubleSpinBox *altitudeSpin;
    QDoubleSpinBox *headingSpin;
    QDoubleSpinBox *speedSpin;
    RadarModel currentModel;
};