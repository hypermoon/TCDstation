#ifndef PRESETDIAGNOSISEDITDIALOG_H
#define PRESETDIAGNOSISEDITDIALOG_H

#include <QDialog>

namespace Ui {
class PresetDiagnosisEditDialog;
}

class PresetDiagnosisEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PresetDiagnosisEditDialog(QWidget *parent = 0);
    ~PresetDiagnosisEditDialog();

    void SetPresetDiagnosis(const QString &diagnosis);
    QString GetPresetDiagnosis();

private slots:
    void on_cancelButton_clicked();

private:
    Ui::PresetDiagnosisEditDialog *ui;
};

#endif // PRESETDIAGNOSISEDITDIALOG_H
