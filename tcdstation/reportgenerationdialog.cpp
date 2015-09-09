#include "reportgenerationdialog.h"
#include "ui_reportgenerationdialog.h"
#include "presetdiagnosisdialog.h"
#include "reportprintsetting.h"
#include "tcdimage.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDir>
#include <QDebug>
#include <QPixmap>
#include <QPrinter>
#include <QPainter>
#include <QPrintDialog>
#include <QScrollArea>


ReportGenerationDialog::ReportGenerationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReportGenerationDialog),patientTracker(NULL)
{
    ui->setupUi(this);
    ui->presetDiagnosisComboBox->setEnabled(true);
    ui->diagnosisEditor->setEnabled(false);

    ui->screenshotListView->setModel(&screenshotModel);
    ui->screenshotListView->setIconSize(QSize(225, 225));

    ui->selectedScreenshotListView->setModel(&selectedScreenshotModel);
    ui->selectedScreenshotListView->setIconSize(QSize(175, 175));

    QScrollArea *area = new QScrollArea(this);
    area->move(10, 90);
    area->resize(781, 600);
    area->setWidget(ui->centreWidget);

    ui->tcdInfoTableView->setModel(&selectedValuesModel);
    QStringList headerList;
    headerList << "截图" << "血管名" << "Mean" << "Peak" << "EDV" << "PI" << "RI" << "S/D" << "HR";
    selectedValuesModel.setHorizontalHeaderLabels(headerList);


    QFile file("./PresetDiagnoses.txt");
    QTextStream in;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(NULL, "预设诊断读取", "预设诊断读取失败！");
    }
    else
    {
        in.setDevice(&file);
        QString line;
        line = in.readLine();
        while (!line.isNull()) {
            ui->presetDiagnosisComboBox->addItem(line);
            diagnosesModel.appendRow(new QStandardItem(line));
            line = in.readLine();
        }
    }
}

ReportGenerationDialog::~ReportGenerationDialog()
{
    delete ui;
}

void ReportGenerationDialog::SetPatientTracker(PatientTracker *tracker)
{
    if (tracker != NULL)
    {
        patientTracker = tracker;
        loadBasicInfo();
        loadImages();
        loadSelectedImagesAndValues();
        loadDiagnosis();
    }
}

void ReportGenerationDialog::on_presetDiagnosisCheckBox_stateChanged(int arg1)
{
    ui->presetDiagnosisComboBox->setEnabled(arg1 == Qt::Checked);
    ui->diagnosisEditor->setEnabled(arg1 == Qt::Unchecked);
}

void ReportGenerationDialog::on_presetDiagnosisEditButton_clicked()
{
    PresetDiagnosisDialog dialog;
    dialog.SetPresetDiagnoses(&diagnosesModel);
    dialog.exec();

    ui->presetDiagnosisComboBox->clear();
    QFile file("./PresetDiagnoses.txt");
    QTextStream out;
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(NULL, "预设诊断存储", "预设诊断存储失败！");
    }
    else
    {
        out.setDevice(&file);
        for (int i = 0; i < diagnosesModel.rowCount(); ++i)
        {
            QString text = diagnosesModel.item(i)->text();
            ui->presetDiagnosisComboBox->addItem(text);
            out << text << endl;
        }
    }
}

void ReportGenerationDialog::on_screenshotListView_doubleClicked(const QModelIndex &index)
{
    QStandardItem *item = screenshotModel.item(ui->screenshotListView->currentIndex().row());
    selectedScreenshotModel.appendRow(new QStandardItem(item->icon(), item->text()));
    processScreenshotAnalysis(item->text());
    screenshotModel.removeRow(ui->screenshotListView->currentIndex().row());
}

void ReportGenerationDialog::on_selectedScreenshotListView_doubleClicked(const QModelIndex &index)
{
    int row = ui->selectedScreenshotListView->currentIndex().row();
    QStandardItem *item = selectedScreenshotModel.item(row);
    screenshotModel.appendRow(new QStandardItem(item->icon(), item->text()));
    selectedScreenshotModel.removeRow(row);
    selectedValuesModel.removeRow(row);
}

void ReportGenerationDialog::loadBasicInfo()
{
    ui->medicalRecordNumberEditor->setText(patientTracker->Data().patient.strChartNumber);
    ui->hospitalizationNumberEditor->setText(patientTracker->Data().patient.strAdmissionNumber);
    ui->dataGatherDate->setText(patientTracker->Data().patient.strDate);
    ui->nameEditor->setText(patientTracker->Data().patient.strName);
    ui->genderEditor->setText(patientTracker->Data().patient.strGender);
    ui->ageEditor->setText(QString::number(patientTracker->Data().patient.nAge));
    ui->heightEditor->setText(QString::number(patientTracker->Data().patient.qHeight));
    ui->weightEditor->setText(QString::number(patientTracker->Data().patient.qWeight));
}

void ReportGenerationDialog::loadImages()
{
    QString patientPath = patientTracker->GetPatientFolderPath();
    QDir patientDir(patientPath);
    QStringList imageList = patientDir.entryList(QStringList("*.png"), QDir::Files, QDir::Name);
    foreach(QString image, imageList)
    {
        screenshotModel.appendRow(new QStandardItem(QIcon(patientPath + "\\" + image), image));
    }
}

void ReportGenerationDialog::loadSelectedImagesAndValues()
{
    int tcdDataCount = patientTracker->GetTCDDataCounts();
    TCDData tcdData[10] = patientTracker->Data().data;
    for (int i = 0; i < tcdDataCount; ++i)
    {
        TCDData tempData = tcdData[i];
        QString picName = tempData.pictureName;
        QIcon icon(patientTracker->GetPatientFolderPath() + "\\" + picName);
        selectedScreenshotModel.appendRow(new QStandardItem(icon, picName));

        QList<QStandardItem *> itemList;
        itemList << new QStandardItem(picName);
        itemList << new QStandardItem(tempData.name);
        itemList << new QStandardItem(QString::number(tempData.qMean));
        itemList << new QStandardItem(QString::number(tempData.qPeak));
        itemList << new QStandardItem(QString::number(tempData.qEDV));
        itemList << new QStandardItem(QString::number(tempData.qPI));
        itemList << new QStandardItem(QString::number(tempData.qRI));
        itemList << new QStandardItem(QString::number(tempData.qSD));
        itemList << new QStandardItem(QString::number(tempData.qHR));
        selectedValuesModel.appendRow(itemList);
    }
}

void ReportGenerationDialog::loadDiagnosis()
{

}

void ReportGenerationDialog::saveDiagnosis()
{
    Diagnosis diagnosis;
    if (ui->presetDiagnosisCheckBox->isChecked())
    {
        diagnosis.text = ui->presetDiagnosisComboBox->currentText();
    }
    else
    {
        diagnosis.text = ui->diagnosisEditor->toPlainText();
    }

    patientTracker->AppendDiagnosis(diagnosis);
}

void ReportGenerationDialog::saveValues()
{
    int rowCount = selectedValuesModel.rowCount();
    for (int i = 0; i < rowCount; ++i)
    {
        TCDData data;
        data.pictureName = selectedValuesModel.item(i, 0)->text();
        data.name = selectedValuesModel.item(i, 1)->text();
        data.qMean = selectedValuesModel.item(i, 2)->text().toFloat();
        data.qPeak = selectedValuesModel.item(i, 3)->text().toFloat();
        data.qEDV = selectedValuesModel.item(i, 4)->text().toFloat();
        data.qPI = selectedValuesModel.item(i, 5)->text().toFloat();
        data.qRI = selectedValuesModel.item(i, 6)->text().toFloat();
        data.qSD = selectedValuesModel.item(i, 7)->text().toFloat();
        data.qHR = selectedValuesModel.item(i, 8)->text().toFloat();
        patientTracker->AppendTCDData(data);
    }
}

void ReportGenerationDialog::on_pushButton_2_clicked()
{
    if(patientTracker == NULL)
    {
        QMessageBox msg(QMessageBox::Warning,
                        tr("错误提示"),
                        tr("没有可用的病人信息！"),
                        QMessageBox::Ok,0 );
        msg.exec();
        return;
    }
    saveDiagnosis();
    saveValues();

    patientTracker->SetPatientReportStatus();
    patientTracker->Save();

}

void ReportGenerationDialog::processScreenshotAnalysis(const QString &imageName)
{
    QImage image(patientTracker->GetPatientFolderPath() + "\\" + imageName);
    //QImage bloodNameImage = image.copy(93, 0, 90, 25);
    //bloodNameImage.save("./bloodname.png");
    //QImage valuesImage = image.copy(0, 30, 590, 50);
    //valuesImage.save("./values.png");
    TcdImage imageAnalyzer;
    //QString bloodName = imageAnalyzer.GetPictureNumber(bloodNameImage);
    //qDebug() << "bloodName: " << bloodName << endl;
    //QStringList values = imageAnalyzer.GetnDataValues(valuesImage);
    imageAnalyzer.LoadWholeImage(image);

    QString bloodName = imageAnalyzer.GetBloodType();

    QStringList values = imageAnalyzer.GetnDataValues();

    foreach(QString string, values)
    {
        qDebug() << string << endl;
    }

    //TODO: add analyzed data into table model
    QList<QStandardItem *> itemList;
    itemList << new QStandardItem(imageName);
    itemList << new QStandardItem(bloodName);
    foreach(QString value, values)
    {
        itemList << new QStandardItem(value);
    }
    selectedValuesModel.appendRow(itemList);
}

void ReportGenerationDialog::on_printBtn_clicked()
{
    on_pushButton_2_clicked();
    if(patientTracker == NULL)
    {
        return;
    }
    QPrinter printer;
    QPrintDialog printDialog(&printer);
   // QString output("report.pdf");


    printer.setOrientation(QPrinter::Portrait);
    printer.setPageSize(QPrinter::A4);
   // printer.setOutputFormat(QPrinter::PdfFormat);
   // printer.setOutputFileName(output);


    if(printDialog.exec() == QDialog::Accepted)
    {
        QPainter painter(&printer);
        ReportPrintSetting reportSetting;
        reportSetting.SetReportForm(painter);

        reportSetting.SetPatient(patientTracker);
        reportSetting.SetReportContent(painter);
    }
}
