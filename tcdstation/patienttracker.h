#ifndef PATIENTTRACKER_H
#define PATIENTTRACKER_H

#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDir>
#include <QMap>
#include <QList>
#include <QTime>
#include "dataformatdef.h"


class PatientTracker
{
public:
    PatientTracker(const QString path="");
    ~PatientTracker();

    bool AppendPatientInfo(const PatientInfo& info);
    bool AppendTCDData(const TCDData& data);
    bool AppendDiagnosis(const Diagnosis& diag);
    bool AppendSelectedPictureName(const QString& name);

    const PatientInfo GetPatientInfo() const;
    const QList<TCDData> GetTCDData() const;
    const Diagnosis GetDiagnosis() const;
    const QStringList GetSelectedPictureName() const;

    void SetReportPredefine(bool bStatus = true);
    bool GetReportPredefine() const;

    // 保存报告信息。
    bool Save();

    // 设置报告生成状态。
    void SetPatientReportStatus(bool bStatus = true);

    // 生成报告时间
    void SetProducedReportTime(const QTime time);

    // 获取报告生成状态
    bool GetPatientReportStatus() const;

    // 删除patient数据。
    bool RemovePatient();

    // 移除当前选中的编辑图片
    bool RemoveSelectedPicture(const QString picname);

    // 获取XML文件路径。
    const QString& GetPatientInfoPath() const;

    // 获取Patient文件夹路径
    const QString& GetPatientFolderPath() const;

    // 获取图片路径。
    QStringList GetPictureName(const QString path);

    // 获取Patient数据
    const PatientData Data() const;

    // 获取解析TCD数据个数
    int GetTCDDataCounts() const;

    // 获取选取图片个数
    int GetSelectedPictureCounts() const;
private:
    bool createPatientFolder();
    bool createPatientXML();

    void writeReportXml();
    bool readReportXml(const QString path);

    bool LoadPatient(const QString path);
    bool findPictureName(const QString path, QStringList& list);

private:
    QMap<QString,TCDData>  m_TcdDataContainer;
    QString             m_PatientFilePath;
    QString             m_PatientFolderPath;

    PatientData         m_ReportData;
    QStringList         m_PictureNamelt;

    QFile               m_file;
    QXmlStreamWriter    m_XmlWriter;
    QXmlStreamReader    m_XmlReader;

    QStringList         m_SelectedPicture;
    bool                m_IsWriteTcdData;
    bool                m_IsWriteDiagnosis;
    bool                m_IsPredefine;
    int                 m_nCount;
    int                 m_nSelectedPictureCounts;
};

#endif // PATIENTTRACKER_H
