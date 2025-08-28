#pragma once
#include <QDialog>
#include "TargetModelDAO.h"
#include "RcsDataDAO.h"

class QLineEdit;
class QTableWidget;
class QPushButton;
class QDoubleSpinBox;
class QComboBox; // 添加前置声明

class TargetModelEditDialog : public QDialog {
    Q_OBJECT
public:
    explicit TargetModelEditDialog(QWidget *parent = nullptr);
    explicit TargetModelEditDialog(int targetId, QWidget *parent = nullptr);
    
    TargetModel getTargetModel() const;
    
private slots:
    void onSaveTarget();
    void onCreateRcs();
    void onEditRcs();
    void onDeleteRcs();
    void onRcsSelectionChanged();
    
private:
    void initUI();
    void loadTargetData();
    void loadRcsData();
    
    QLineEdit *nameEdit;
    // QLineEdit *typeEdit;
    QComboBox *typeCombo; // 添加这行
    // QLineEdit *longitudeEdit;
    // QLineEdit *latitudeEdit;
    // QLineEdit *altitudeEdit;
    QDoubleSpinBox *longitudeSpin;
    QDoubleSpinBox *latitudeSpin;
    QDoubleSpinBox *altitudeSpin;
    QDoubleSpinBox *headingSpin;
    QDoubleSpinBox *speedSpin;
    
    QTableWidget *rcsTable;
    QPushButton *editRcsBtn;
    QPushButton *deleteRcsBtn;
    
    int targetId;
    bool isEditMode;
    TargetModel currentModel;
};