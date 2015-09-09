#include "producedreportpage.h"
#include "ui_producedreportpage.h"
#include "reportgenerationdialog.h"
#include "reportprintsetting.h"

#include <QPrinter>
#include <QPainter>
#include <QPrintDialog>
#include <QMessageBox>

ProducedReportPage::ProducedReportPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProducedReportPage)
{
    ui->setupUi(this);
    this->setWindowTitle("已生成报告窗口");
    m_patientModel = new PatientModel(this,PatientModel::ProducedReport);
    ui->tableView->setModel(m_patientModel);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->verticalHeader()->setVisible(false);
    for(int i=0; i<5; i++)
    {
        ui->tableView->setColumnWidth(i, 150);
    }
}

ProducedReportPage::~ProducedReportPage()
{
    delete ui;
}


void ProducedReportPage::on_enterBtn_clicked()
{
    QString searchInfo = ui->lineEdit->text();
    if(!searchInfo.isEmpty())
    {
        m_patientModel->QueryPatientByName(searchInfo);
    }
}

void ProducedReportPage::on_editBtn_clicked()
{
    if(m_modelIndex.isValid())
    {
        PatientTracker* const pPatient =  m_patientModel->GetPatient(m_modelIndex);
        ReportGenerationDialog dialog;
        dialog.SetPatientTracker(pPatient);
        dialog.exec();
    }
    else
    {
        QMessageBox msg(QMessageBox::Warning,
                                            tr("错误提示"),
                                            tr("请先选择需要编辑的病人！"),
                                            QMessageBox::Ok,0 );
        msg.exec();
    }
}

void ProducedReportPage::on_deleteBtn_clicked()
{
    if(m_modelIndex.isValid())
    {
        m_patientModel->RemovePatient(m_modelIndex);
    }
    else
    {
        QMessageBox msg(QMessageBox::Warning,
                                            tr("错误提示"),
                                            tr("请先选择需要删除的病人！"),
                                            QMessageBox::Ok,0 );
        msg.exec();
    }
}

void ProducedReportPage::on_printBtn_clicked()
{
    if( m_modelIndex.isValid())
    {
        QPrinter printer;
        QPrintDialog printDialog(&printer);
        //QString output("report.pdf");


        //printer.setPageSize(QSizeF(printer.logicalDpiX()*(210/25.4),printer.logicalDpiY()*(297/25.4)));
        printer.setOrientation(QPrinter::Portrait);
        printer.setPageSize(QPrinter::A4);
       // printer.setOutputFormat(QPrinter::PdfFormat);
       // printer.setOutputFileName(output);


        if(printDialog.exec() == QDialog::Accepted)
        {
            QPainter painter(&printer);
            ReportPrintSetting reportSetting;
            reportSetting.SetReportForm(painter);

            PatientTracker* pPatient =  m_patientModel->GetPatient(m_modelIndex);
            reportSetting.SetPatient(pPatient);
            reportSetting.SetReportContent(painter);
        }
    }
    else
    {
        QMessageBox msg(QMessageBox::Warning,
                                            tr("错误提示"),
                                            tr("请先选择需要打印的病人！"),
                                            QMessageBox::Ok,0 );
        msg.exec();
    }

}

void ProducedReportPage::on_closeBtn_clicked()
{
    this->close();
}



void ProducedReportPage::on_lineEdit_textChanged(const QString &arg1)
{
    if(arg1.isEmpty())
    {
        m_patientModel->TraversePatient();
    }
}

void ProducedReportPage::on_tableView_clicked(const QModelIndex &index)
{
    m_modelIndex = index;
}
