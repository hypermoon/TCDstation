#ifndef UNTREATEDREPORT_H
#define UNTREATEDREPORT_H

#include <QDialog>
#include <QModelIndex>
#include "patientmodel.h"

namespace Ui {
class UntreatedReport;
}

class UntreatedReport : public QDialog
{
    Q_OBJECT

public:
    explicit UntreatedReport(QWidget *parent = 0);
    ~UntreatedReport();

private slots:
    void on_BnSearch_clicked();
    void on_BnSpace_clicked();
    void on_BnDelete_clicked();

    void on_BnCancel_clicked();

    void on_ClientList_clicked(const QModelIndex &index);
    void on_SearchEdit_textChanged(const QString &arg1);

private:
    Ui::UntreatedReport *ui;
    QString m_strSearchInfo;
    PatientModel *m_pModel;
    QModelIndex  m_curIndex;
};

#endif // UNTREATEDREPORT_H
