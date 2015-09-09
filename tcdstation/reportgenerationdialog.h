#ifndef REPORTGENERATIONDIALOG_H
#define REPORTGENERATIONDIALOG_H

#include <QDialog>
#include <QStandardItemModel>
#include <QImage>
#include "patienttracker.h"
namespace Ui {
class ReportGenerationDialog;
}

class ReportGenerationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReportGenerationDialog(QWidget *parent = 0);
    ~ReportGenerationDialog();

    void SetPatientTracker(PatientTracker *tracker);

private slots:

    void on_presetDiagnosisCheckBox_stateChanged(int arg1);

    void on_presetDiagnosisEditButton_clicked();

    void on_screenshotListView_doubleClicked(const QModelIndex &index);

    void on_selectedScreenshotListView_doubleClicked(const QModelIndex &index);

    void on_pushButton_2_clicked();

    void on_printBtn_clicked();

private:
    void processScreenshotAnalysis(const QString &imageName);

private:
    void loadBasicInfo();
    void loadImages();
    void loadSelectedImagesAndValues();
    void loadDiagnosis();
    void saveDiagnosis();
    void saveValues();

private:
    Ui::ReportGenerationDialog *ui;

    QStandardItemModel diagnosesModel;

    QStandardItemModel screenshotModel;
    QStandardItemModel selectedScreenshotModel;
    QStandardItemModel selectedValuesModel;

    PatientTracker *patientTracker;
};

#endif // REPORTGENERATIONDIALOG_H
