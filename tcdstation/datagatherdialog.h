#ifndef DATAGATHERDIALOG_H
#define DATAGATHERDIALOG_H

#include <QDialog>
#include <QStandardItemModel>
#include <QList>
#include <QImage>
#include <QKeyEvent>
#include <QTimer>
#include "patienttracker.h"
#include "videostreamhandler.h"
namespace Ui {
class DataGatherDialog;
}

class DataGatherDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DataGatherDialog(QWidget *parent = 0);
    ~DataGatherDialog();
protected:
    void keyPressEvent(QKeyEvent *);

    void mouseReleaseEvent(QMouseEvent *);

signals:
    void idScanned(const QString&);

private slots:
    void on_screenshotButton_clicked();

    void on_saveButton_clicked();

    void on_generateReportButton_clicked();

    void handleIdScanned(const QString &id);

    void handleTimeout();

private:
    void savePatientInfo();
    void clearAll();

private:
    Ui::DataGatherDialog *ui;
    QStandardItemModel model;
    QList<QImage> images;
    PatientTracker *patient;

    QString id;

    VideoStreamHandler videoStreamHandler;
    QRect clipRect;
    QTimer timer;
};

#endif // DATAGATHERDIALOG_H
