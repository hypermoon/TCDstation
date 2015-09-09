#include "presetdiagnosiseditdialog.h"
#include "ui_presetdiagnosiseditdialog.h"

PresetDiagnosisEditDialog::PresetDiagnosisEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PresetDiagnosisEditDialog)
{
    ui->setupUi(this);
}

PresetDiagnosisEditDialog::~PresetDiagnosisEditDialog()
{
    delete ui;
}

void PresetDiagnosisEditDialog::SetPresetDiagnosis(const QString &diagnosis)
{
    ui->plainTextEdit->setPlainText(diagnosis);
}

QString PresetDiagnosisEditDialog::GetPresetDiagnosis()
{
    return ui->plainTextEdit->toPlainText();
}

void PresetDiagnosisEditDialog::on_cancelButton_clicked()
{
    ui->plainTextEdit->clear();
}
