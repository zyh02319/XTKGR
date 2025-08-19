#pragma once
#include <QDialog>
#include <QLabel>
#include "JammerModelDAO.h"

class JammerModelViewDialog : public QDialog {
    Q_OBJECT
public:
    explicit JammerModelViewDialog(const JammerModel& model, QWidget *parent = nullptr);

private:
    void setupUI(const JammerModel& model);
};