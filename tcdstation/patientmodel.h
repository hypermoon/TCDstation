#ifndef PATIENTMODEL_H
#define PATIENTMODEL_H

#include <QAbstractTableModel>
#include <QStringList>
#include <QMap>
#include <QMultiMap>
#include <QDir>
#include <QFile>
#include <QFileInfoList>
#include "patienttracker.h"


class PatientModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    typedef enum{
        UnproducedReport,   // 未生产报告数据
        ProducedReport      // 已生成报告数据
    }EnumModel;
public:
    PatientModel(QObject* parent=0, EnumModel model = ProducedReport);
    virtual ~PatientModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,int role = Qt::DisplayRole) const;

    bool RemovePatient(const QModelIndex &index, bool bUpdate = false);
    PatientTracker* GetPatient(const QModelIndex &index);
    void TraversePatient();
    bool QueryPatientByName(const QVariant strName);

private:
    void freeMap();
    void triageData();
    void traverseDir();
    QString currencyAt(int offset) const;
    QString getText(const QModelIndex &index);

private:
    QMap<QString, PatientTracker*> m_PatientMap;
    QMultiMap<QString, QString> m_QueryMap;
    QStringList    m_PatientDirList;
    QStringList    m_ResultList;
protected:
    int m_EnumModel;
};

#endif // PATIENTMODEL_H
