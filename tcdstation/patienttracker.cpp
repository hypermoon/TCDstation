#include "patienttracker.h"
#include <QUuid>
#include <QDebug>

PatientTracker::PatientTracker(const QString path)
{
    m_IsWriteTcdData = false;
    m_IsWriteDiagnosis = false;
    m_IsPredefine = true;
    m_nCount = 0;
    m_nSelectedPictureCounts = 0;

    m_PictureNamelt.clear();
    m_ReportData.bProducedReport = false;
    if (path.isEmpty())
    {
        if (createPatientFolder())
        {
            m_PatientFilePath = m_PatientFolderPath + "/Patient.xml";
        }
    }
    else
    {
        m_PatientFolderPath = path;
        m_PatientFilePath = m_PatientFolderPath + "/Patient.xml";
        LoadPatient(m_PatientFilePath);
        findPictureName(m_PatientFolderPath, m_PictureNamelt);
    }
}


PatientTracker::~PatientTracker()
{

}

bool PatientTracker::AppendPatientInfo(const PatientInfo &info)
{
    m_ReportData.patient = info;

    return true;
}

bool PatientTracker::AppendTCDData(const TCDData &data)
{
    m_IsWriteTcdData = true;  
    int nindex = m_TcdDataContainer.size();
    m_ReportData.data[nindex] = data;
    m_TcdDataContainer.insert( data.pictureName, data);
    return true;
}

bool PatientTracker::AppendDiagnosis(const Diagnosis &diag)
{
    m_ReportData.text = diag;
    m_IsWriteDiagnosis = true;
    return true;
}

bool PatientTracker::AppendSelectedPictureName(const QString &name)
{
    if (name.isEmpty())
        return false;
    m_SelectedPicture.append(name);
    m_nSelectedPictureCounts++;
    return true;
}

const PatientInfo PatientTracker::GetPatientInfo() const
{
    return m_ReportData.patient;
}

const QList<TCDData> PatientTracker::GetTCDData() const
{
    QList<TCDData> dataList;
    for(int i=0; i<m_nCount; i++)
    {
        dataList.append(m_ReportData.data[i]);
    }
    return dataList;
}

const Diagnosis PatientTracker::GetDiagnosis() const
{
    return m_ReportData.text;
}

const QStringList PatientTracker::GetSelectedPictureName() const
{
    return m_SelectedPicture;
}

void PatientTracker::SetReportPredefine(bool bStatus)
{
    m_IsPredefine = bStatus;
}

bool PatientTracker::GetReportPredefine() const
{
    return m_IsPredefine;
}

bool PatientTracker::Save()
{
    if ( m_IsWriteTcdData || m_IsWriteDiagnosis )
    {
        m_ReportData.bProducedReport = true;
    }
    m_nCount = m_TcdDataContainer.size();

    bool bRet = createPatientXML();
    if(bRet)
    {
        writeReportXml();
    }

    return bRet;
}

bool PatientTracker::LoadPatient(const QString path)
{
    return readReportXml(path);
}

void PatientTracker::SetPatientReportStatus(bool bStatus)
{
    m_ReportData.bProducedReport = bStatus;
}

void PatientTracker::SetProducedReportTime(const QTime time)
{
    m_ReportData.strDate = time.toString();
}

bool PatientTracker::GetPatientReportStatus() const
{
    return m_ReportData.bProducedReport;
}

bool PatientTracker::RemovePatient()
{
    QDir dir;
    QStringList dirNames;
    QFileInfoList filelist;
    QFileInfoList::iterator curfile;

    dirNames.clear();
    if (dir.exists())
    {
        dirNames<<m_PatientFolderPath;
    }
    else
    {
        return false;
    }
    for(int i=0; i<dirNames.size(); ++i)
    {
        dir.setPath(dirNames[i]);
        filelist = dir.entryInfoList(QDir::Dirs | QDir::Files | QDir::Readable | QDir::Writable
                                     |QDir::Hidden |QDir::NoDotAndDotDot, QDir::Name);
        if (filelist.size()>0)
        {
            curfile = filelist.begin();
            while(curfile != filelist.end())
            {
                if(curfile->isDir())
                {
                    dirNames.push_back(curfile->filePath());
                }
                else
                {
                    if( !dir.remove(curfile->fileName()))
                    {
                        return false;
                    }
                }
                curfile++;
            }

        }
    }

    for(int i=dirNames.size()-1; i>=0; --i)
    {
        dir.setPath(dirNames[i]);
        if(!dir.rmdir("."))
        {
            return false;
        }
    }

    return true;
}

bool PatientTracker::RemoveSelectedPicture(const QString picname)
{
   if (picname.isEmpty())
       return false;

   if (!m_SelectedPicture.removeOne(picname))
       return false;

   m_nSelectedPictureCounts--;

/*    QMap<QString, TCDData>::const_iterator Iter = m_TcdDataContainer.find(picname);
    if (Iter == m_TcdDataContainer.end())
        return false;

    m_TcdDataContainer.erase(m_TcdDataContainer.find(picname));*/
    return true;
}

const QString &PatientTracker::GetPatientInfoPath() const
{
    return m_PatientFilePath;
}

const QString &PatientTracker::GetPatientFolderPath() const
{
    return m_PatientFolderPath;
}

QStringList PatientTracker::GetPictureName(const QString path)
{
    QStringList list;
    findPictureName(path, list);

    return list;
}

const PatientData PatientTracker::Data() const
{
    return m_ReportData;
}

int PatientTracker::GetTCDDataCounts() const
{
    return m_nCount;
}

int PatientTracker::GetSelectedPictureCounts() const
{
    return m_nSelectedPictureCounts;
}

bool PatientTracker::createPatientFolder()
{
    QDir dir;
    QUuid uid = QUuid::createUuid();

    QString folderPath = dir.currentPath() + "\\Patient";
    if (!dir.exists(folderPath))
    {
        if (dir.mkdir(folderPath))
        {
            folderPath = folderPath + "\\" + uid.toString();
            if (dir.mkdir(folderPath))
            {
                m_PatientFolderPath = folderPath;
            }
            else
                return false;
        }
        else
            return false;
    }
    else
    {
        folderPath = folderPath + "\\" + uid.toString();
        if (dir.mkdir(folderPath))
        {
            m_PatientFolderPath = folderPath;
        }
        else
            return false;
    }
    return true;
}

bool PatientTracker::createPatientXML()
{
    if(m_PatientFilePath.isEmpty())
    {
        return false;
    }

    m_file.setFileName(m_PatientFilePath);
    if (!m_file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        return false;
    }

    return true;
}

void PatientTracker::writeReportXml()
{
    m_XmlWriter.setDevice(&m_file);
    m_XmlWriter.setAutoFormatting(true);
    m_XmlWriter.writeStartDocument();
    m_XmlWriter.writeStartElement("TCDStationXML");
    if(m_ReportData.bProducedReport)
    {
         m_XmlWriter.writeAttribute("Status", "TRUE");
    }
    else
    {
         m_XmlWriter.writeAttribute("Status", "FALSE");
    }

    m_XmlWriter.writeStartElement("patientInfo");
    m_XmlWriter.writeTextElement("Chart_Number", m_ReportData.patient.strChartNumber);
    m_XmlWriter.writeTextElement("Admission_Number", m_ReportData.patient.strAdmissionNumber);
    m_XmlWriter.writeTextElement("Gender", m_ReportData.patient.strGender);
    m_XmlWriter.writeTextElement("Name", m_ReportData.patient.strName);
    m_XmlWriter.writeTextElement("Age", QString::number(m_ReportData.patient.nAge, 10));
    m_XmlWriter.writeTextElement("Height", QString::number(m_ReportData.patient.qHeight));
    m_XmlWriter.writeTextElement("Weight", QString::number(m_ReportData.patient.qWeight));
    m_XmlWriter.writeTextElement("Detecting_Date", m_ReportData.patient.strDate);
    m_XmlWriter.writeEndElement();

    if (!m_SelectedPicture.isEmpty())
    {
        m_XmlWriter.writeStartElement("SelectedPicture");
        m_XmlWriter.writeAttribute("size", QString::number(m_SelectedPicture.size()));
        for(int i=0; i<m_SelectedPicture.size(); i++)
        {
            m_XmlWriter.writeStartElement("Picture");
            m_XmlWriter.writeTextElement("uri", m_SelectedPicture.at(i));
            m_XmlWriter.writeEndElement();
        }
        m_XmlWriter.writeEndElement();
    }

    if (m_IsWriteTcdData)
    {
        QMap<QString, TCDData>::const_iterator iter = m_TcdDataContainer.begin();
        for (int i=0; i<m_nCount; i++)
        {
            if (iter != m_TcdDataContainer.end())
            {
                m_XmlWriter.writeStartElement("TCDData");
                m_XmlWriter.writeAttribute("name", iter.value().name);
                //m_XmlWriter.writeAttribute("uri", iter.value().pictureName);
                m_XmlWriter.writeTextElement("Mean", QString::number(iter.value().qMean));
                m_XmlWriter.writeTextElement("Peak", QString::number(iter.value().qPeak));
                m_XmlWriter.writeTextElement("EDV", QString::number(iter.value().qEDV));
                m_XmlWriter.writeTextElement("PI", QString::number(iter.value().qPI));
                m_XmlWriter.writeTextElement("RI", QString::number(iter.value().qRI));
                m_XmlWriter.writeTextElement("SD", QString::number(iter.value().qSD));
                m_XmlWriter.writeTextElement("HR", QString::number(iter.value().qHR));
                m_XmlWriter.writeEndElement();
                iter++;
            }
        }
    }
    if (m_IsWriteDiagnosis)
    {
        m_XmlWriter.writeStartElement("Diagnosis");
        if(m_IsPredefine)
        {
           m_XmlWriter.writeAttribute("type", "Predefine");
        }
        else
        {
           m_XmlWriter.writeAttribute("type", "Custom");
        }

        m_XmlWriter.writeTextElement("Text", m_ReportData.text.text);
        m_XmlWriter.writeEndElement();
        m_XmlWriter.writeTextElement("Doctor", m_ReportData.text.name);
        m_XmlWriter.writeTextElement("Produced_Date", m_ReportData.strDate);
    }
    m_XmlWriter.writeEndDocument();
    m_file.close();
}

bool PatientTracker::readReportXml(const QString path)
{
    int nIndex = -1;
    m_file.setFileName(path);
    if (m_file.open(QFile::ReadOnly | QFile::Text))
    {
        m_XmlReader.setDevice(&m_file);

        while(!m_XmlReader.atEnd())
        {
            QXmlStreamReader::TokenType type =  m_XmlReader.readNext();
            QXmlStreamAttributes attribute =  m_XmlReader.attributes();
            if(attribute.hasAttribute("Status"))
            {
                if (attribute.value("Status").toString() == "TRUE")
                {
                    m_ReportData.bProducedReport = true;
                }
                else
                {
                    m_ReportData.bProducedReport = false;
                }
            }
            if (type == QXmlStreamReader::StartDocument)
                continue;

            if (type == QXmlStreamReader::StartElement)
            {

                if (m_XmlReader.name() == "TCDStationXML")
                    continue;

                if (m_XmlReader.name() == "PatientInfo")
                    continue;

                if (m_XmlReader.name() == "TCDData")
                {
                    ++nIndex;
                    m_ReportData.bProducedReport = true;

                    if (attribute.hasAttribute("name"))
                    {
                        m_ReportData.data[nIndex].name =  attribute.value("name").toString();
                    }
//                    if (attribute.hasAttribute("uri"))
//                    {
//                        m_SelectedPicture.append(attribute.value("uri").toString());
//                        m_ReportData.data[nIndex].pictureName = attribute.value("uri").toString();
//                    }
                    continue;
                }
                if (m_XmlReader.name() == "SelectedPicture")
                {
                    if (attribute.hasAttribute("size"))
                    {
                        m_nSelectedPictureCounts = attribute.value("size").toInt();
                    }
                    continue;
                }

                if (m_XmlReader.name() == "uri")
                {
                    m_SelectedPicture.append(m_XmlReader.readElementText());
                }
                if( m_XmlReader.name() == "Diagnosis")
                {
                    QXmlStreamAttributes attribute =  m_XmlReader.attributes();
                    if (attribute.hasAttribute("type"))
                    {
                        if (attribute.value("type").toString() == "Predefine")
                        {
                            m_IsPredefine = true;
                        }
                        else
                        {
                            m_IsPredefine = false;
                        }
                    }
                    continue;
                }

                if (m_XmlReader.name() == "Chart_Number")
                {
                    m_ReportData.patient.strChartNumber = m_XmlReader.readElementText();
                    continue;
                }
                else if (m_XmlReader.name() == "Admission_Number")
                {
                    m_ReportData.patient.strAdmissionNumber = m_XmlReader.readElementText();
                    continue;
                }
                else if (m_XmlReader.name() == "Name")
                {
                    m_ReportData.patient.strName = m_XmlReader.readElementText();
                    continue;
                }
                else if (m_XmlReader.name() == "Gender")
                {
                    m_ReportData.patient.strGender = m_XmlReader.readElementText();
                    continue;
                }
                else if (m_XmlReader.name() == "Age")
                {
                    m_ReportData.patient.nAge = m_XmlReader.readElementText().toInt();
                    continue;
                }
                else if (m_XmlReader.name() == "Height")
                {
                    m_ReportData.patient.qHeight = m_XmlReader.readElementText().toFloat();
                    continue;
                }
                else if (m_XmlReader.name() == "Weight")
                {
                    m_ReportData.patient.qWeight = m_XmlReader.readElementText().toFloat();
                    continue;
                }
                else if (m_XmlReader.name() == "Detecting_Date")
                {
                    m_ReportData.patient.strDate = m_XmlReader.readElementText();
                }

                if (m_XmlReader.name() == "Mean")
                {
                    m_ReportData.data[nIndex].qMean = m_XmlReader.readElementText().toFloat();
                    continue;
                }
                else if (m_XmlReader.name() == "Peak")
                {
                    m_ReportData.data[nIndex].qPeak = m_XmlReader.readElementText().toFloat();
                    continue;
                }
                else if (m_XmlReader.name() == "EDV")
                {
                    m_ReportData.data[nIndex].qEDV = m_XmlReader.readElementText().toFloat();
                    continue;
                }
                else if (m_XmlReader.name() == "PI")
                {
                    m_ReportData.data[nIndex].qPI = m_XmlReader.readElementText().toFloat();
                    continue;
                }
                else if (m_XmlReader.name() == "SD")
                {
                    m_ReportData.data[nIndex].qSD= m_XmlReader.readElementText().toFloat();
                    continue;
                }
                else if (m_XmlReader.name() == "HR")
                {
                    m_ReportData.data[nIndex].qHR = m_XmlReader.readElementText().toFloat();
                    continue;
                }

                if (m_XmlReader.name() == "Text")
                {
                    m_ReportData.text.text = m_XmlReader.readElementText();
                }
                else if(m_XmlReader.name() == "Doctor")
                {
                    m_ReportData.text.name = m_XmlReader.readElementText();
                }

                if(m_XmlReader.name() == "Produced_Date")
                {
                    m_ReportData.strDate = m_XmlReader.readElementText();
                }
            }
        }
    }
    else
        return false;

    m_nCount = nIndex + 1;
    m_file.close();
    return true;
}

bool PatientTracker::findPictureName(const QString path, QStringList &list)
{
    QDir dir;
    QFileInfoList filelist;
    QFileInfoList::iterator curfile;

    dir.setPath( path );
    filelist = dir.entryInfoList(QDir::Dirs | QDir::Files | QDir::Readable | QDir::Writable
                                 |QDir::Hidden |QDir::NoDotAndDotDot, QDir::Name);
    if (filelist.size()>0)
    {
        curfile = filelist.begin();
        while(curfile != filelist.end())
        {
            list.append(curfile->filePath());
            curfile++;
        }
    }
    else
        return false;

    return true;
}
