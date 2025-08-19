#pragma once
#include <QDialog>
#include "TargetModelWithRcs.h"

class QTextEdit;
class QTableWidget;

class TargetModelViewDialog : public QDialog {
    Q_OBJECT
public:
    explicit TargetModelViewDialog(const TargetModelWithRcs& model, QWidget *parent = nullptr);
    
private:
    void initUI();
    
    TargetModelWithRcs targetModel;
    QTextEdit *modelInfoText;
    QTableWidget *rcsTable;
};