#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "untreatedreport.h"
#include "datagatherdialog.h"
#include "producedreportpage.h"
#include "reportformdefinition.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ReportFormDefinition report;
    report.WriteReportForm();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_dataGatherButton_clicked()
{
    DataGatherDialog dialog;
    dialog.exec();
}

void MainWindow::on_UnproducedReportButton_clicked()
{
    UntreatedReport unReportDialog;
    unReportDialog.exec();
}

void MainWindow::on_producedReportButton_clicked()
{
    ProducedReportPage dialog;
    dialog.exec();
}
