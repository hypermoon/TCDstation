#ifndef DATAFORMATDEF_H
#define DATAFORMATDEF_H

#include <QString>
//  病人基本信息
typedef struct PATIENTINFO_tag
{
    QString strChartNumber;      // 病历号
    QString strAdmissionNumber;  // 住院号
    int     nAge;              // 年龄
    qreal   qHeight;           // 身高
    qreal   qWeight;           // 体重
    QString strName;           // 姓名
    QString strGender;         // 性别
    QString strDate;           // 检测时间
    PATIENTINFO_tag()
    {
        strChartNumber = "";
        strAdmissionNumber = "";
        nAge = 0;
        qHeight = 0.0;
        qWeight = 0.0;
    }
}PatientInfo, *pPatientInfo;

// TCD 数据
typedef struct TCDDATA_tag
{
    qreal   qMean;
    qreal   qPeak;
    qreal   qEDV;
    qreal   qPI;
    qreal   qRI;
    qreal   qSD;
    qreal   qHR;
    QString name;           // 血管名称
    QString pictureName;    // 对应图片名称

    TCDDATA_tag()
    {
        qMean = 0.0;
        qPeak = 0.0;
        qEDV = 0.0;
        qPI = 0.0;
        qRI = 0.0;
        qSD = 0.0;
        qHR = 0.0;
    }

}TCDData, *pTCDData;

// 医生诊断内容
typedef struct DIAGNOSIS_tag
{
    QString text;  // 诊断内容
    QString name;  // 医生签名
    bool    isPredefined ;
}Diagnosis, *pDiagnosis;

// 报告书内容
typedef struct PATIENRDATA_tag
{
    bool                bProducedReport;  // 是否已生成报告
    QString             strDate;          // 生成报告时间
    PatientInfo         patient;          // 病人基本信息
    TCDData             data[10];          // TCD 数据
    Diagnosis           text;             // 医嘱
}PatientData;

#endif // DATAFORMATDEF_H
