#ifndef REPORTFORMDEFINITION_H
#define REPORTFORMDEFINITION_H

#include <QObject>
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QVector>


enum Report
{Title,Splitter1,Splitter2,Splitter3,
    BasicInfoTitle,MedRecordNo,AdmissionNo,CheckDate,PatientName,Gender,Age,Height,Weight,
    MedRecordContent,AdmissionContent,CheckDateContent,NameContent,GenderContent,AgeContent,HeightContent,WeightContent,
    TcdTitle, ImgOne, ImgTwo,ImgThree,ImgFour,
    VesselNameOne,DataMeanOne,DataPeakOne,DataEdvOne,DataPiOne,DataRiOne,DataSdOne,DataHrOne,
    VesselNameTwo,DataMeanTwo,DataPeakTwo,DataEdvTwo,DataPiTwo,DataRiTwo,DataSdTwo,DataHrTwo,
    VesselNameThree,DataMeanThree,DataPeakThree,DataEdvThree,DataPiThree,DataRiThree,DataSdThree,DataHrThree,
    VesselNameFour,DataMeanFour,DataPeakFour,DataEdvFour,DataPiFour,DataRiFour,DataSdFour,DataHrFour,
    VesselValueOne,MeanValueOne,PeakValueOne,EdvValueOne,PIValueOne,RIValueOne,SDValueOne,HRValueOne,
    VesselValueTwo,MeanValueTwo,PeakValueTwo,EdvValueTwo,PIValueTwo,RIValueTwo,SDValueTwo,HRValueTwo,
    VesselValueThree,MeanValueThree,PeakValueThree,EdvValueThree,PIValueThree,RIValueThree,SDValueThree,HRValueThree,
    VesselValueFour,MeanValueFour,PeakValueFour,EdvValueFour,PIValueFour,RIValueFour,SDValueFour,HRValueFour,
    DiagnoseTitle,Signature,DiagnoseContent,SignatureContent,
    Notice
};


class ReportFormDefinition : public QObject
{
    Q_OBJECT
public:
    explicit ReportFormDefinition(QObject *parent = 0);
    void WriteReportForm();
    void ReadReportContent(QString &fileName);

    void GetPosition(int num,QRectF& rect);

protected:

    void writeBasicInfoForm(QXmlStreamWriter &writer);
    void writeTCDScreenShot(QXmlStreamWriter &writer);
    void writeTCDDataForm(QXmlStreamWriter &writer);
    void writeDiagnose(QXmlStreamWriter &writer);
    void writeNotice(QXmlStreamWriter &writer);

    void readBasicInfo(QXmlStreamReader &reader);
    void readTCDScreenShot(QXmlStreamReader &reader);
    void readTCDData(QXmlStreamReader &reader);
    void readTCDDataOne(QXmlStreamReader &reader);
    void readTCDDataTwo(QXmlStreamReader &reader);
    void readTCDDataThree(QXmlStreamReader &reader);
    void readTCDDataFour(QXmlStreamReader &reader);
    void readDiagnose(QXmlStreamReader &reader);
    void readNotice(QXmlStreamReader &reader);

    void readPosition(QXmlStreamReader &reader,QVector<QString> &vec,QString startName);
    void clearVector();
signals:

public slots:

private:

    int m_pageWidth;
    int m_pageHeight;
    int m_imgCount;
    int m_currentY;
    int m_titleHeight;
    int m_basicInfoHeight;
    int m_tcdScreenShotHeight;
    int m_tcdDataHeight;
    int m_tcdEachDataHeight;
    int m_diagnoseHeight;
    int m_startXPos;

    // Title
    QVector<QString> m_titleVec;

    //BasicInfo
    QVector<QString> m_basicInfoTitleVec;
    QVector<QString> m_MedRecordNOVec;
    QVector<QString> m_AdmissionNOVec;
    QVector<QString> m_CheckDateVec;
    QVector<QString> m_NameVec;
    QVector<QString> m_GenderVec;
    QVector<QString> m_AgeVec;
    QVector<QString> m_heightVec;
    QVector<QString> m_weightVec;

    QVector<QString> m_MedRecordNOContentVec;
    QVector<QString> m_AdmissionNOContentVec;
    QVector<QString> m_CheckDateContentVec;
    QVector<QString> m_NameContentVec;
    QVector<QString> m_GenderContentVec;
    QVector<QString> m_AgeContentVec;
    QVector<QString> m_heightContentVec;
    QVector<QString> m_weightContentVec;

    //Screen shot
    QVector<QString> m_screenShotVec;
    QVector<QString> m_ImgOneVec;
    QVector<QString> m_ImgTwoVec;
    QVector<QString> m_ImgThreeVec;
    QVector<QString> m_ImgFourVec;

    //TCD Data
    QVector<QString> m_vesselNameOne;
    QVector<QString> m_vesselValueOne;

    QVector<QString> m_vesselNameTwo;
    QVector<QString> m_vesselValueTwo;

    QVector<QString> m_vesselNameThree;
    QVector<QString> m_vesselValueThree;

    QVector<QString> m_vesselNameFour;
    QVector<QString> m_vesselValueFour;

    QVector<QString> m_dataOneMeanVec;
    QVector<QString> m_dataOnePeakVec;
    QVector<QString> m_dataOneEDVVec;
    QVector<QString> m_dataOnePIVec;
    QVector<QString> m_dataOneRIVec;
    QVector<QString> m_dataOneSDVec;
    QVector<QString> m_dataOneHRVec;

    QVector<QString> m_dataTwoMeanVec;
    QVector<QString> m_dataTwoPeakVec;
    QVector<QString> m_dataTwoEDVVec;
    QVector<QString> m_dataTwoPIVec;
    QVector<QString> m_dataTwoRIVec;
    QVector<QString> m_dataTwoSDVec;
    QVector<QString> m_dataTwoHRVec;

    QVector<QString> m_dataThreeMeanVec;
    QVector<QString> m_dataThreePeakVec;
    QVector<QString> m_dataThreeEDVVec;
    QVector<QString> m_dataThreePIVec;
    QVector<QString> m_dataThreeRIVec;
    QVector<QString> m_dataThreeSDVec;
    QVector<QString> m_dataThreeHRVec;

    QVector<QString> m_dataFourMeanVec;
    QVector<QString> m_dataFourPeakVec;
    QVector<QString> m_dataFourEDVVec;
    QVector<QString> m_dataFourPIVec;
    QVector<QString> m_dataFourRIVec;
    QVector<QString> m_dataFourSDVec;
    QVector<QString> m_dataFourHRVec;

    QVector<QString> m_meanOneContent;
    QVector<QString> m_peakOneContent;
    QVector<QString> m_edvOneContent;
    QVector<QString> m_piOneContent;
    QVector<QString> m_riOneContent;
    QVector<QString> m_sdOneContent;
    QVector<QString> m_hrOneContent;

    QVector<QString> m_meanTwoContent;
    QVector<QString> m_peakTwoContent;
    QVector<QString> m_edvTwoContent;
    QVector<QString> m_piTwoContent;
    QVector<QString> m_riTwoContent;
    QVector<QString> m_sdTwoContent;
    QVector<QString> m_hrTwoContent;

    QVector<QString> m_meanThreeContent;
    QVector<QString> m_peakThreeContent;
    QVector<QString> m_edvThreeContent;
    QVector<QString> m_piThreeContent;
    QVector<QString> m_riThreeContent;
    QVector<QString> m_sdThreeContent;
    QVector<QString> m_hrThreeContent;

    QVector<QString> m_meanFourContent;
    QVector<QString> m_peakFourContent;
    QVector<QString> m_edvFourContent;
    QVector<QString> m_piFourContent;
    QVector<QString> m_riFourContent;
    QVector<QString> m_sdFourContent;
    QVector<QString> m_hrFourContent;

    QVector<QString> m_diagnoseVec;
    QVector<QString> m_contentVec;
    QVector<QString> m_signatureVec;
    QVector<QString> m_sigContentVec;

    //Splitter
    QVector<QString> m_splitterOneVec;
    QVector<QString> m_splitterTwoVec;
    QVector<QString> m_splitterThreeVec;

    //notice
    QVector<QString> m_noticeVec;
};

#endif // REPORTFORMDEFINITION_H
