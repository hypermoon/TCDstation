#include "untreatedreport.h"
#include "ui_untreatedreport.h"
#include "reportgenerationdialog.h"
#include "patienttracker.h"
#include <QMessageBox>
#include <qdebug.h>

UntreatedReport::UntreatedReport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UntreatedReport)
{
    ui->setupUi(this);
    m_pModel = new PatientModel(this, PatientModel::UnproducedReport);
    ui->ClientList->setModel(m_pModel);
    ui->ClientList->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->ClientList->verticalHeader()->setVisible(false);
    for(int i=0; i<5; i++)
    {
        ui->ClientList->setColumnWidth(i, 150);
    }
    ui->ClientList->show();
}

UntreatedReport::~UntreatedReport()
{
    delete ui;
}

void UntreatedReport::on_BnSearch_clicked()
{
    m_strSearchInfo = ui->SearchEdit->text();
    if (!m_strSearchInfo.isEmpty())
    {
        m_pModel->QueryPatientByName(m_strSearchInfo);
    }
}

void UntreatedReport::on_BnSpace_clicked()
{
    if(m_curIndex.isValid())
    {
        PatientTracker* const pPatient =  m_pModel->GetPatient(m_curIndex);
        if(pPatient == NULL)
            return;
        ReportGenerationDialog dialog;
        dialog.SetPatientTracker(pPatient);
        dialog.exec();

        if (pPatient->GetPatientReportStatus())
        {
            m_pModel->RemovePatient(m_curIndex, true);
        }
    }
    else
    {
        QMessageBox msg(QMessageBox::Warning,
                                           tr("错误提示"),
                                           tr("请先选择有效的病人！"),
                                            QMessageBox::Ok,0 );
        msg.exec();
    }
}

void UntreatedReport::on_BnDelete_clicked()
{
    if (m_curIndex.isValid())
    {
          m_pModel->RemovePatient(m_curIndex);
    }
    else
    {
        QMessageBox msg(QMessageBox::Warning,
                                           tr("错误提示"),
                                           tr("请先选择有效的病人！"),
                                            QMessageBox::Ok,0 );
        msg.exec();
    }

}

void UntreatedReport::on_BnCancel_clicked()
{
    this->close();
}

void UntreatedReport::on_ClientList_clicked(const QModelIndex &index)
{
    m_curIndex = index;
}

void UntreatedReport::on_SearchEdit_textChanged(const QString &arg1)
{
    if (arg1.isEmpty())
    {
        m_pModel->TraversePatient();
    }
}

