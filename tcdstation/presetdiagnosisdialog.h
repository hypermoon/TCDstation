#ifndef PRESETDIAGNOSISDIALOG_H
#define PRESETDIAGNOSISDIALOG_H

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class PresetDiagnosisDialog;
}

class PresetDiagnosisDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PresetDiagnosisDialog(QWidget *parent = 0);
    ~PresetDiagnosisDialog();

    void SetPresetDiagnoses(QStandardItemModel *diagnoses);
private slots:
    void on_newButton_clicked();

    void on_acceptButton_clicked();

    void on_editButton_clicked();

    void on_deleteButton_clicked();

    void on_presetDiagnosisListView_clicked(const QModelIndex &index);

private:
    Ui::PresetDiagnosisDialog *ui;
    QStandardItemModel *diagnosesModel;
    QStandardItemModel tempModel;
};

#endif // PRESETDIAGNOSISDIALOG_H
