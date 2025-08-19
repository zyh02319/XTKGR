#pragma once
#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QDoubleSpinBox>
#include "JammerModelDAO.h"

class JammerModelEditDialog : public QDialog {
    Q_OBJECT
public:
    explicit JammerModelEditDialog(QWidget *parent = nullptr);
    JammerModelEditDialog(const JammerModel& model, QWidget *parent = nullptr);
    JammerModel getJammerModel() const;

private:
    void setupUI();
    QLineEdit *nameEdit;
    QComboBox *jammingTypeCombo;
    QDoubleSpinBox *powerSpin;
    QDoubleSpinBox *bandwidthSpin;
    QDoubleSpinBox *gainSpin;
    QDoubleSpinBox *longitudeSpin;
    QDoubleSpinBox *latitudeSpin;
    QDoubleSpinBox *altitudeSpin;
    JammerModel currentModel;
};