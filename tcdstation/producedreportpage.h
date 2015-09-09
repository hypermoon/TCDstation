#ifndef PRODUCEDREPORTPAGE_H
#define PRODUCEDREPORTPAGE_H

#include <QDialog>
#include "patientmodel.h"

namespace Ui {
class ProducedReportPage;
}

class ProducedReportPage : public QDialog
{
    Q_OBJECT

public:
    explicit ProducedReportPage(QWidget *parent = 0);
    ~ProducedReportPage();

private slots:
    void on_enterBtn_clicked();

    void on_editBtn_clicked();

    void on_deleteBtn_clicked();

    void on_printBtn_clicked();

    void on_closeBtn_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::ProducedReportPage *ui;

    PatientModel *m_patientModel;

    QModelIndex m_modelIndex;
};

#endif // PRODUCEDREPORTPAGE_H
