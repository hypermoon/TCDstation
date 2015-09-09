#ifndef REPORTPRINTSETTING_H
#define REPORTPRINTSETTING_H


#include <QObject>
#include <QPainter>
#include <QFont>
#include <QDebug>
#include <QRectF>
#include <QPixmap>
#include <QTableView>
#include <QStandardItemModel>

#include "reportformdefinition.h"
#include "patienttracker.h"

//#define TEXT 0
//#define SPLITTER 1
//#define IMAGE 2

enum DrawType
{
    TEXT, SPLITTER,IMAGE,WIDGET
};

#define IMGCOUNTS 4
class ReportPrintSetting : public QObject
{
    Q_OBJECT
public:
    explicit ReportPrintSetting(QObject *parent = 0);
    ~ReportPrintSetting();

    void SetReportForm(QPainter &painter);
    void SetReportContent(QPainter &painter);
    void SetPatient(PatientTracker *tracker);
 private:
    void drawPosition(int type, QString content,QPainter &painter,
                      int drawType = TEXT,QString img="",
                      int fontSize=15,
                      const QString family="SimSun",

                      bool bold=false);

private:
    void initTableView();
signals:

public slots:

private:
    PatientTracker *m_patientTracker;
    QTableView *m_tableView;
    QStandardItemModel *m_tableModel;

};

#endif // REPORTPRINTSETTING_H
