#include "presetdiagnosisdialog.h"
#include "ui_presetdiagnosisdialog.h"
#include "presetdiagnosiseditdialog.h"
#include <QDebug>
PresetDiagnosisDialog::PresetDiagnosisDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PresetDiagnosisDialog)
{
    ui->setupUi(this);
    ui->presetDiagnosisListView->setModel(&tempModel);
    ui->editButton->setEnabled(false);
    ui->deleteButton->setEnabled(false);
}

PresetDiagnosisDialog::~PresetDiagnosisDialog()
{
    delete ui;
}

void PresetDiagnosisDialog::SetPresetDiagnoses(QStandardItemModel *diagnoses)
{
    diagnosesModel = diagnoses;
    for (int i = 0; i < diagnosesModel->rowCount(); ++i)
    {
        tempModel.appendRow(new QStandardItem(diagnosesModel->item(i)->text()));
    }
}

void PresetDiagnosisDialog::on_newButton_clicked()
{
    PresetDiagnosisEditDialog dialog;
    if (dialog.exec() == QDialog::Accepted)
    {
        QStandardItem *item = new QStandardItem(dialog.GetPresetDiagnosis());
        tempModel.appendRow(item);
    }
}

void PresetDiagnosisDialog::on_acceptButton_clicked()
{
    diagnosesModel->clear();
    for (int i = 0; i < tempModel.rowCount(); ++i)
    {
        diagnosesModel->appendRow(new QStandardItem(tempModel.item(i)->text()));
    }
}

void PresetDiagnosisDialog::on_editButton_clicked()
{
    QStandardItem *item = tempModel.item(ui->presetDiagnosisListView->currentIndex().row());
    PresetDiagnosisEditDialog dialog;
    dialog.SetPresetDiagnosis(item->text());
    if (dialog.exec() == QDialog::Accepted)
    {
        item->setText(dialog.GetPresetDiagnosis());
    }
}

void PresetDiagnosisDialog::on_deleteButton_clicked()
{
    tempModel.removeRow(ui->presetDiagnosisListView->currentIndex().row());
    if (tempModel.rowCount() <= 0)
    {
        ui->editButton->setEnabled(false);
        ui->deleteButton->setEnabled(false);
    }
}

void PresetDiagnosisDialog::on_presetDiagnosisListView_clicked(const QModelIndex &index)
{
    ui->editButton->setEnabled(true);
    ui->deleteButton->setEnabled(true);
}
