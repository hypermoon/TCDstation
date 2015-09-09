#ifndef GETPATIENTINFOMATION_H
#define GETPATIENTINFOMATION_H
#include <QJsonObject>
#include <QObject>
#include <QFile>
#include <QXmlStreamReader>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>


typedef struct __PATINFO
{
    QPair<QString,QString> ID_Customer ; //体检号
    QPair<QString,QString> ID_bedNO   ;  //住院号
    QPair<QString,QString> Name;         //名字
    QPair<QString,QString> Marrage;      //marry
    QPair<QString,QString> Gender;       //gender
    QPair<QString,QString> Birth;        //birthday
    QPair<QString,QString> IDCard;       //idcard
    QPair<QString,QString> MobileNO;     //mobilenum
    QPair<QString,QString> Photobase64;   //photo
    QPair<QString,QString> Age;            //age
    QPair<QString,QString> Bodyheight;      //bodyheigh
    QPair<QString,QString> Bodyweight;        //bodyweight
    QPair<QString,QString> Reserve1;           //reserve1;
    QPair<QString,QString> Reserve2;          //reserve2;
    QPair<QString,QString> Reserve3;         //reserve3;
}PATINFO;

class GetPatientInfomation :public QObject
{
    Q_OBJECT
public:
    explicit GetPatientInfomation(QObject *parent = 0);

    //外部调用接口,传入查询所需三个字符串
    void GetPatientsInfo(QString interface, QString authcode, QString str);

    //外部调用接口,设置服务器查询网址
    void SetServiceUrl(QString strurl);


    ~ GetPatientInfomation();
protected:
    void SetParameter(QString interface,QString authcode,QString strid);


    bool WriteJsonFile( ) ; //QString jsonFilePath);

  signals:
      void ReceivedResponse(QJsonObject);                   //the signal to recive QJSon file of PatientINFO
  signals:
      void Errcode(QNetworkReply::NetworkError);            //the status of errcode;
private:
   void  InitialPatientStruct();

   void  dataToPic(QString fromData, QString toPic, QString myformat);

    //test func
public:
      bool writeXMLfile();

      bool readXMLfile();

      QString m_serverstr;

      QNetworkRequest        m_req;
      QNetworkReply          *pm_replay;
      QNetworkAccessManager  m_netmanager;

private:

      PATINFO m_patientinfo;

      QString  m_interfacetype;
      QString  m_authcode;
      QString  m_strid;

      QJsonObject m_json;

      QFile *m_pLogFile;

      QXmlStreamReader xmlprocess;
      QFile *m_pFile;

public  slots:

      //void ReadyforAnalysis();
      //void readyReads();
      void networkError(QNetworkReply::NetworkError); //int errortype);
      void finishDownload();
};
// typedef QString (*PGETCUSTBASEINFO)(QString sinterfacetype,QString sauthorcode,QString customerid);
#endif // QGETPATIENTINFOMATION_H
