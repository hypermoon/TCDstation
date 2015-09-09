#include "datagatherdialog.h"
#include "ui_datagatherdialog.h"
#include "reportgenerationdialog.h"

#include <QDebug>
#include <QDate>
#include <QTime>
DataGatherDialog::DataGatherDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataGatherDialog),
    patient(NULL),
    clipRect(145,68,600,470)
{
    ui->setupUi(this);
    ui->screenshotListview->setModel(&model);
    connect(this, SIGNAL(idScanned(QString)), SLOT(handleIdScanned(QString)));
    setFocus();
    timer.setInterval(30);
    timer.start();
    connect(&timer, SIGNAL(timeout()), this, SLOT(handleTimeout()));
}

DataGatherDialog::~DataGatherDialog()
{
    delete ui;
}

void DataGatherDialog::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    if (key >= '0' && key <= '9')
    {
        id += QChar(key);
    }
    else if (key == Qt::Key_Enter || key == Qt::Key_Return)
    {
        idScanned(id);
        id = "";
    }
}

void DataGatherDialog::mouseReleaseEvent(QMouseEvent *)
{
    setFocus();
}

void DataGatherDialog::on_screenshotButton_clicked()
{
    if (patient == NULL)
    {
        patient = new PatientTracker();
    }
    ui->tcdScreenLabel->pixmap()->save(patient->GetPatientFolderPath() + "\\" + QString::number(model.rowCount()+1) + ".png");

    QStandardItem *item = new QStandardItem(QIcon(*ui->tcdScreenLabel->pixmap()), QString::number(model.rowCount()+1));
    model.appendRow(item);
    ui->screenshotListview->scrollTo(ui->screenshotListview->model()->index(model.rowCount()-1, 0));
}

void DataGatherDialog::on_saveButton_clicked()
{
    savePatientInfo();

    if (patient != NULL)
    {
        patient = NULL;
        delete patient;
    }

    clearAll();
}

void DataGatherDialog::on_generateReportButton_clicked()
{
    savePatientInfo();
    ReportGenerationDialog dialog;
    dialog.SetPatientTracker(patient);
    dialog.exec();
}

void DataGatherDialog::handleIdScanned(const QString &id)
{
    qDebug() << "id scanned: " << id << endl;
}

void DataGatherDialog::handleTimeout()
{
    QImage image = videoStreamHandler.GetImage().copy(clipRect);
    ui->tcdScreenLabel->setPixmap(QPixmap::fromImage(image));
}

void DataGatherDialog::savePatientInfo()
{
    if (patient != NULL)
    {
        PatientInfo info;
        info.strChartNumber = ui->medicalRecordNumberEditor->text();
        info.strAdmissionNumber = ui->hospitalizationNumberEditor->text();
        info.strName = ui->nameEditor->text();
        info.strGender = ui->genderEditor->text();
        info.nAge = ui->ageEditor->text().toInt();
        info.qHeight = ui->heightEditor->text().toFloat();
        info.qWeight = ui->weightEditor->text().toFloat();
        info.strDate = QDate::currentDate().toString("yyyy.MM.dd");

        patient->AppendPatientInfo(info);
        patient->Save();
    }
}

void DataGatherDialog::clearAll()
{
    ui->medicalRecordNumberEditor->clear();
    ui->hospitalizationNumberEditor->clear();
    ui->nameEditor->clear();
    ui->genderEditor->clear();
    ui->ageEditor->clear();
    ui->heightEditor->clear();
    ui->weightEditor->clear();

    model.clear();
}
