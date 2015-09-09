#include "patientmodel.h"
#include <QTime>
#include <QDebug>

PatientModel::PatientModel( QObject* parent, EnumModel model)
    :QAbstractTableModel(parent),m_EnumModel(model)
{
    TraversePatient();
}

PatientModel::~PatientModel()
{
    freeMap();
}

int PatientModel::rowCount(const QModelIndex &parent) const
{
    return m_PatientMap.count();
}

int PatientModel::columnCount(const QModelIndex &parent) const
{
    // Name, ChartNo, Age, Gender, date;
    return 5;
}

QVariant PatientModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_PatientMap.size())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        QString rowCurrency =currencyAt(index.row());

        if (index.column() ==0)
        {
            return m_PatientMap.value(rowCurrency)->Data().patient.strName;
        }
        else if(index.column() == 1)
        {
            return m_PatientMap.value(rowCurrency)->Data().patient.strChartNumber;
        }
        if (index.column() ==2)
        {
            return QString::number(m_PatientMap.value(rowCurrency)->Data().patient.nAge);
        }
        else if(index.column() == 3)
        {
            return m_PatientMap.value(rowCurrency)->Data().patient.strGender;
        }
        else if(index.column() == 4)
        {
            return m_PatientMap.value(rowCurrency)->Data().patient.strDate;
        }
        return QVariant();
    }
    else
        return QVariant();
}

QVariant PatientModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation == Qt::Horizontal)
    {
        if (section == 0)
        {
            return QVariant("姓名");
        }
        else if (section == 1)
        {
            return QVariant("病历号");
        }
        else if (section == 2)
        {
            return QVariant("年龄");
        }
        else if (section == 3)
        {
            return QVariant("性别");
        }
        else if (section == 4)
        {
            return QVariant("就诊日期");
        }
    }
    return currencyAt(section);
}

bool PatientModel::RemovePatient(const QModelIndex &index, bool bUpdate)
{
    QString strIndex = getText(index);

    QMap<QString, PatientTracker *>::const_iterator Iter = m_PatientMap.find( strIndex );
    if (Iter != m_PatientMap.end())
    {
        beginResetModel();
        if (!bUpdate)
        {
            Iter.value()->RemovePatient();
        }

        PatientTracker* pPatient = Iter.value();

        delete pPatient;
        m_PatientMap.erase(m_PatientMap.find( strIndex ));
        endResetModel();
    }
    else
        return false;
    return true;
}

PatientTracker *PatientModel::GetPatient(const QModelIndex &index)
{
    QString strIndex = getText(index);

    QMap<QString, PatientTracker *>::const_iterator Iter = m_PatientMap.find( strIndex );
    if (Iter != m_PatientMap.end())
        return m_PatientMap.find( strIndex ).value();

    return NULL;
}

void PatientModel::TraversePatient()
{
    traverseDir();
    if (m_PatientDirList.size())
    {
        freeMap();
        beginResetModel();
        for (int i=0; i<m_PatientDirList.size(); i++)
        {
            PatientTracker* pPatient = new PatientTracker(m_PatientDirList.at(i));
            if (m_EnumModel == ProducedReport )
            {
                if (pPatient->GetPatientReportStatus())
                {
                    QString strName = pPatient->Data().patient.strName;
                    QString strNumber = pPatient->Data().patient.strChartNumber;
                    m_PatientMap.insert(strName +" | "+ strNumber , pPatient);
                    m_QueryMap.insert(strName, strName +" | "+ strNumber);
                }
            }
            else if(m_EnumModel == UnproducedReport)
            {
                if (!pPatient->GetPatientReportStatus())
                {
                    QString strName = pPatient->Data().patient.strName;
                    QString strNumber = pPatient->Data().patient.strChartNumber;
                    m_PatientMap.insert(strName +" | "+ strNumber , pPatient);
                    m_QueryMap.insert(strName, strName +" | "+ strNumber);
                }
            }
            endResetModel();
        }
    }
}

bool PatientModel::QueryPatientByName(const QVariant strName)
{
    m_ResultList = m_QueryMap.values(strName.toString());
    triageData();

    return true;
}


void PatientModel::triageData()
{
    beginResetModel();
    QMap<QString, PatientTracker*>::Iterator Iter = m_PatientMap.begin();
    while (Iter != m_PatientMap.end())
    {
        bool bRet = false;
        for(int i=0; i<m_ResultList.size(); i++)
        {
            if (Iter.key() == m_ResultList.at(i))
            {
                bRet = true;
            }
        }

        if (!bRet)
        {
            delete Iter.value();
            m_PatientMap.erase(Iter++);
        }
        else
        {
            Iter++;
        }
    }
    endResetModel();
}

void PatientModel::traverseDir()
{
    QDir dir;
    QFileInfoList filelist;
    QFileInfoList::iterator curfile;

    m_PatientDirList.clear();
    QString folderPath = dir.currentPath() + "\\Patient";

    dir.setPath(folderPath);
    filelist = dir.entryInfoList(QDir::Dirs | QDir::Readable | QDir::Writable | QDir::Hidden |QDir::NoDotAndDotDot, QDir::Name);
    if (filelist.size()>0)
    {
        curfile = filelist.begin();
        while(curfile != filelist.end())
        {
            if(curfile->isDir())
            {
                m_PatientDirList.push_back(curfile->filePath());
            }
            curfile++;
        }
    }
}

void PatientModel::freeMap()
{
    QMap<QString, PatientTracker*>::const_iterator Iter = m_PatientMap.begin();
    while (Iter != m_PatientMap.end())
    {
        delete Iter.value();
        Iter++;
    }
}

QString PatientModel::currencyAt(int offset) const
{
    return (m_PatientMap.begin() + offset).key();
}

QString PatientModel::getText(const QModelIndex &index)
{
    QString strName = index.child(index.row(), 0).data().toString();
    QString strChartNumber = index.child(index.row(), 1).data().toString();

    return strName + " | " + strChartNumber;
}








