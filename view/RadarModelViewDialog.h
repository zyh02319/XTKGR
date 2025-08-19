#pragma once
#include <QDialog>
#include <QLabel>
#include "RadarModelDAO.h"

class RadarModelViewDialog : public QDialog {
    Q_OBJECT
public:
    explicit RadarModelViewDialog(const RadarModel& model, QWidget *parent = nullptr);

private:
    void setupUI(const RadarModel& model);
};