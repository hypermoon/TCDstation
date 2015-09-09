#include "getpatientinfomation.h"
#include <QtGui/QImage>
#include <QFile>
#include <QTextCodec>

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QDebug>

GetPatientInfomation::GetPatientInfomation(QObject *parent ):
QObject(parent)
{
  m_pFile = new QFile("ServerReplyFile.txt");
  if(m_pFile->open(QIODevice::WriteOnly|QIODevice::Text))
  {
      ;//qDebug()<<"file opened! " << endl;
  }
  else
  {
      ;//qDebug() << "file not opend!" <<  endl;
  }

  m_pLogFile = new QFile("TraceLogFile.log");
  if(m_pLogFile->open(QIODevice::WriteOnly|QIODevice::Text))
  {
      m_pLogFile->write("1.  LogFile Opened! \r\n");
      qDebug()<<"log file opened! " << endl;
  }
  else
  {
      m_pLogFile->write("1.  LogFile Not Opened! \r\n");

      qDebug()<<"log file opened! " << endl;

  }

  m_pLogFile->flush();

  m_serverstr = "http://192.170.1.2/WebService/CustomerWS.asmx/";
  InitialPatientStruct();

  //connect(this,SIGNAL(filewrited),this,SLOT(QGetPatientInfomation::ReadyforAnalysis));


}

GetPatientInfomation::~GetPatientInfomation()
{
    if(m_pLogFile->handle() != NULL)
    {
        m_pLogFile->flush();
        m_pLogFile->close();
    }


}

void GetPatientInfomation::InitialPatientStruct()
{
    m_patientinfo.Age.first = "年龄";
    m_patientinfo.Age.second = QString();

    m_patientinfo.Birth.first = "生日";
    m_patientinfo.Birth.second = QString();

    m_patientinfo.Bodyheight.first = "身高";
    m_patientinfo.Bodyheight.second = QString();

    m_patientinfo.Bodyweight.first = "体重";
    m_patientinfo.Bodyweight.second = QString();

    m_patientinfo.Gender.first = "性别";
    m_patientinfo.Gender.second = QString();

    m_patientinfo.IDCard.first ="身份证号";
    m_patientinfo.IDCard.second = QString();

    m_patientinfo.ID_bedNO.first = "病床号";
    m_patientinfo.ID_bedNO.second = QString();

    m_patientinfo.ID_Customer.first = "病历号";
    m_patientinfo.ID_Customer.second = QString();

    m_patientinfo.Marrage.first = "婚姻";
    m_patientinfo.Marrage.second = QString();

    m_patientinfo.MobileNO.first = "手机";
    m_patientinfo.MobileNO.second = QString();

    m_patientinfo.Name.first = "姓名";
    m_patientinfo.Name.second = QString(); //assign null to it

    m_patientinfo.Photobase64.first = "图像";
    m_patientinfo.Photobase64.second = QString();

    m_patientinfo.Reserve1.first = "保留1";
    m_patientinfo.Reserve1.second = QString();

    m_patientinfo.Reserve2.first = "保留2";
    m_patientinfo.Reserve2.second = QString();

    m_patientinfo.Reserve3.first = "保留3";
    m_patientinfo.Reserve3.second = QString();

}

//void QGetPatientInfomation::ReadyforAnalysis()
//{
//    readXMLfile();
//}

/*void QGetPatientInfomation::readyReads()
{
    qDebug() <<"readinread get start!!! "  <<endl;
  //m_pFile->write("teststrings");

  if(m_pFile)
  {

     //m_pFile->write(pm_replay->readAll());
     qDebug() <<"readinread get end!!! "  <<endl;
  }
}
*/
void GetPatientInfomation::finishDownload()
{
    if(m_pFile->handle() != NULL)
    {
     // QTextCodec *codec = QTextCodec::codecForName("utf8");

      m_pLogFile->write("\r\n3.  ready to read reply data\r\n");


      QByteArray repleystr = (pm_replay->readAll());

      QString t = repleystr; //codec->toUnicode(repleystr);

      if(m_pFile)
      {

           m_pFile->write(repleystr);
      }

      qDebug() << t << endl;

      m_pLogFile->write(repleystr);

      m_pLogFile->flush();

      m_pFile->flush();
      m_pFile->close();
    }

   // emit(filewrited());
   readXMLfile();

   WriteJsonFile();


}

bool GetPatientInfomation::writeXMLfile()
{
    QFile file("patinfo.xml");
    if(file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        QXmlStreamWriter tmpxml(&file);

        tmpxml.setAutoFormatting(true);
        tmpxml.writeStartDocument();
        tmpxml.writeStartElement("CustomerBaseInfo");
        tmpxml.writeAttribute("xmlns:xsi","http://www.w3.org/2001/XMLSchema-instance");
        tmpxml.writeAttribute("xmlns:xsd","http://www.w3.org/2001/XMLSchema");
        tmpxml.writeTextElement("CustomerID","16032020140002");
        tmpxml.writeTextElement("CustomerName","预约测试001");
        tmpxml.writeTextElement("MarriageName","已婚");
        tmpxml.writeTextElement("Gender","女");
        tmpxml.writeTextElement("BirthDay","2014-03-20");
        tmpxml.writeTextElement("IDCard","111111201403201121");
        tmpxml.writeTextElement("MobileNo","");
        tmpxml.writeTextElement("PhotoBase64Code","DRTERTREJHKHKIDFGERUIOPOIOIPUOIJADSKLFJDSAKLFJDSKLFJDKLSFJLKDSFJDSLKAFJDLKSFJDLKSFJDLKSJFLKDSJDFGSFDGDFEYUTYURYTHGJBVNCVBCVBVCXDCXVCXVCVXCVXCDFFEWREWTYTYTR3RRTWER");
        tmpxml.writeEndElement();
        tmpxml.writeEndDocument();
        file.close();

    }
     qDebug() <<"write is ok!" <<endl;
     return true;

}

bool GetPatientInfomation::readXMLfile()//QString strfilepath)
{
    QString strs;
    int i = 0;
    QFile file("patinfo1.txt");
   // QFile file(strfilepath);

    if(file.open(QFile::ReadOnly | QFile::Text))
    {

        m_pLogFile->write("\r\n4.  Start to analysis XML file\r\n");
        xmlprocess.setDevice(&file);
        while(!xmlprocess.atEnd())
        {
            QXmlStreamReader::TokenType type = xmlprocess.readNext();
            if(type == QXmlStreamReader::StartDocument)
                continue;
            if(type == QXmlStreamReader::StartElement)
            {
                if(xmlprocess.name() == "CustomerBaseInfo")
                {
                      i = 1;
                      continue;
                }
                if(xmlprocess.name() == "CustomerID")
                {
                    strs = xmlprocess.readElementText();
                    m_patientinfo.ID_Customer.second = strs;
                    qDebug() << strs <<endl;
                    i =2;
                    continue;
                }
                if(xmlprocess.name() == "CustomerName")
                {
                    strs = xmlprocess.readElementText();
                    m_patientinfo.Name.second = strs;
                    qDebug() << strs <<endl;
                    i = 3;
                    continue;
                }
                if(xmlprocess.name() == "MarriageName")
                {
                    strs = xmlprocess.readElementText();
                    m_patientinfo.Marrage.second = strs;
                    qDebug() << strs <<endl;
                    i = 4;
                    continue;
                }
                if(xmlprocess.name() == "Gender")
                {
                    strs = xmlprocess.readElementText();
                    m_patientinfo.Gender.second = strs;
                    qDebug() << strs <<endl;
                    i = 5;
                    continue;
                }
                if(xmlprocess.name() == "BirthDay")
                {
                    strs = xmlprocess.readElementText();
                    m_patientinfo.Birth.second = strs;
                    qDebug() << strs <<endl;
                    i = 6;
                    continue;
                }
                if(xmlprocess.name() == "IDCard")
                {
                    strs = xmlprocess.readElementText();
                    m_patientinfo.IDCard.second = strs;
                    qDebug() << strs <<endl;
                    i = 7;
                    continue;
                }
                if(xmlprocess.name() == "MobileNo")
                {
                    strs = xmlprocess.readElementText();
                    m_patientinfo.MobileNO.second =strs;
                    qDebug() << strs <<endl;
                    i = 8;
                    continue;
                }
                if(xmlprocess.name() == "PhotoBase64Code")
                {
                    strs = xmlprocess.readElementText();
                    m_patientinfo.Photobase64.second = strs;
                    qDebug() << strs <<endl;
                    i = 9;

                    dataToPic(strs,"photo.png","base64");
                    continue;
                }

            }
        }

        m_pLogFile->write("5.  XML analysised finished!\r\n");
        m_pLogFile->flush();
    }
     qDebug() <<"read is ok!" <<endl;
     return true;
}

void GetPatientInfomation::SetParameter(QString interface,QString authcode,QString strid)
{

    //http://www.webxml.com.cn/webservices/qqOnlineWebService.asmx
    //QQ:2438767385
    // strurl += " HTTP/1.1";

    QString strparameter;
    QString logstr;

    m_interfacetype = interface;
    m_authcode      = authcode;
    m_strid         = strid;

    QString strurl;

   // QString strurl = "http://www.webxml.com.cn/webservices/qqOnlineWebService.asmx/qqCheckOnline?qqCode=";
   // QString strurl = "http://192.170.1.2/WebService/CustomerWS.asmx/GetCustomerBaseInfo?";

   if(!m_serverstr.isEmpty())
   {
     strparameter = m_serverstr;
     strparameter = strparameter + "/GetCustomerBaseInfo?";

     strparameter += "sInterFaceType=" ;
     strparameter += interface;
     strparameter += "&";

     strparameter += "sAuthorizationCode=" ;
     strparameter +=  authcode;
     strparameter += "&";

     strparameter += "CustomerID";
     strparameter +=  strid;
   }



    strurl = strparameter;

    m_req.setUrl(QUrl(strurl));


    logstr = "2.  Request Get string is  ";
     logstr = logstr + strurl;

    m_pLogFile->write(logstr.toLatin1());

    m_pLogFile->flush();

    pm_replay = m_netmanager.get(m_req);

    // connect(pm_replay,SIGNAL(readyRead()),this, SLOT(readyReads()));



    connect(pm_replay, SIGNAL(finished()),this, SLOT(finishDownload ()));

    connect(pm_replay, SIGNAL(error(QNetworkReply::NetworkError)), this,SLOT(networkError(QNetworkReply::NetworkError)));


}


void GetPatientInfomation::GetPatientsInfo(QString interface, QString authcode, QString str)
{
   SetParameter(interface,authcode,str);
}

void GetPatientInfomation::SetServiceUrl(QString strurl)
{
   m_serverstr = strurl;
}
void GetPatientInfomation::networkError(QNetworkReply::NetworkError err)
{
  // emit(Errcode(QNetworkReply::NetworkError));
    QString str = "\r\nErrorCode: ";
            str += QString::number(err);
            str += "\r\n";
    m_pLogFile->write(str.toLatin1());
    m_pLogFile->flush();
    emit(Errcode(err));
}

bool GetPatientInfomation::WriteJsonFile( ) //QString jsonFilePath)
{

   // QJsonArray jsonArray;

    m_pLogFile->write("6.   Start to Generate JSON file\r\n");
    QJsonObject jsonObject;

    qDebug() <<"json start!" <<endl;

    jsonObject.insert(m_patientinfo.Age.first,  m_patientinfo.Age.second);
    jsonObject.insert(m_patientinfo.Birth.first,m_patientinfo.Birth.second );
    jsonObject.insert(m_patientinfo.Bodyheight.first,m_patientinfo.Bodyheight.second );
    jsonObject.insert(m_patientinfo.Bodyweight.first,m_patientinfo.Bodyweight.second );
    jsonObject.insert(m_patientinfo.Gender.first,m_patientinfo.Gender.second );
    jsonObject.insert(m_patientinfo.IDCard.first,m_patientinfo.IDCard.second );
    jsonObject.insert(m_patientinfo.ID_bedNO.first,m_patientinfo.ID_bedNO.second );
    jsonObject.insert(m_patientinfo.ID_Customer.first,m_patientinfo.ID_Customer.second );
    jsonObject.insert(m_patientinfo.Marrage.first,m_patientinfo.Marrage.second );
    jsonObject.insert(m_patientinfo.MobileNO.first,m_patientinfo.MobileNO.second );
    jsonObject.insert(m_patientinfo.Name.first,m_patientinfo.Name.second );
    jsonObject.insert(m_patientinfo.Photobase64.first,m_patientinfo.Photobase64.second );
    jsonObject.insert(m_patientinfo.Reserve1.first,m_patientinfo.Reserve1.second );
    jsonObject.insert(m_patientinfo.Reserve2.first,m_patientinfo.Reserve2.second );
    jsonObject.insert(m_patientinfo.Reserve3.first,m_patientinfo.Reserve3.second );

    QFile jsonFile( "PatientinfoFile.json" );
    if ( !jsonFile.open( QIODevice::WriteOnly | QIODevice::Text ) )
        return false;

    QTextStream stream( &jsonFile );
    QJsonDocument jsonDoc;
    jsonDoc.setObject( jsonObject );
    stream << jsonDoc.toJson();


    // 5. Close the json file.
    jsonFile.close();

    m_json = jsonObject;
    qDebug() <<"json gened!" <<endl;

    m_pLogFile->write("7.   JSON file generated!\r\n");
    m_pLogFile->flush();


    emit(ReceivedResponse(m_json));

    return true;
}


void GetPatientInfomation::dataToPic(QString fromData, QString toPic, QString myformat)
 {
    // QFile file(fromData);
   // if (file.open(QFile::ReadOnly))
    // {
       //  QByteArray read=file.readAll();
       //  file.close();
       //  QString ss=QString::fromLatin1(read.data(),read.size());

         QByteArray rc;
         QString ss = m_patientinfo.Photobase64.second;

         if (myformat=="Hex")
         {
             rc=QByteArray::fromHex(ss.toLatin1());//toAscii());
         }
         else
         {
             rc=QByteArray::fromBase64(ss.toLatin1());
            // rc=QByteArray::fromBase64("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AAAA4BMCGAAAAAD4hAAGAAAAAD4hgAEAAACATwhgAAAAAOATAhgAAAAA+IQABgAAAAA+IYABAAAAgE8IYAAAAADgEwIYAAAAAPiEAAYAAAAAPiGAAQAAAIBPCGAAAAAA4BMCGAAAAAD4hAAGAAAAAD4hgAEAAACATwhgAAAAAOATAhgAAAAA+IQABgAAAAA+IYABAAAAgE8IYAAAAADgEwIYAAAAAPiEAAYAAAAAPiGAAQAAAIBPCGAAAAAA4BMCGAAAAAD4hAAGAAAAAD4hgAEAAACATwhgAAAAAOATAhgAAAAA+IQABgAAAAA+IYABAAAAgE8IYAAAAADgEwIYAAAAAPiEAAYAAAAAPiGAAQAAAIBPCGAAAAAA4BMCGAAAAAD4hAAGAAAAAD4hgAEAAACATwhgAAAAAOATAhgAAAAA+IQABgAAAAA+IYABAAAAgE8IYAAAAADgEwIYAAAAAPiEAAYAAAAAPiGAAQAAAIBPCGAAAAAA4BMCGAAAAAD4hAAGAAAAAD4hgAEAAACATwhgAAAAAOATAhgAAAAA+IQABgAAAAA+IYABAAAAgE8IYAAAAADgEwIYAAAAAPiEAAYAAAAAPiGAAQAAAIBPCGAAAAAA4BMCGAAAAAD4hAAGAAAAAD4hgAEAAACATwhgAAAAAOATAhgAAAAA+IQABgAAAAA+IYABAAAAgE8IYAAAAADgEwIYAAAAAPiEAAYAAAAAPiGAAQAAAIBPCGAAAAAA4BMCGAAAAAD4hAAGAAAAAD4hgAEAAACATwhgAAAAAOATAhgAAAAA+IQABgAAAAA+IYABAAAAgE8IYAAAAADgEwIYAAAAAPiEAAYAAAAAPiGAAQAAAIBPCGAAAAAA4BMCGAAAAAD4hAAGAAAAAD4hgAEAAACATwhgAAAAAOATAhgAAAAA+IQABgAAAAA+IYABAAAAgE8IYAAAAADgEwIYAAAAAPiEAAYAAAAAPiGAAQAAAIBPCGAAAAAA4BMCGAAAAAD4hAAGAAAAAD4hgAEAAACATwhgAAAAAOATAhgAAAAA+IQABgAAAAA+IYABAAAAgE8IYAAAAADgEwIYAAAAAPiEAAYAAAAAPiGAAQAAAIBPCGAAAAAA4BMCGAAAAAD4hAAGAAAAAD4hgAEAAACATwhgAAAAAOATAhgAAAAA+IQABgAAAAA+IYABAAAAgE8IYAAAAADgEwIYAAAAAPiEAAYAAAAAPiGAAQAAAIBPCGAAAAAA4BMCGAAAAAD4hAAGAAAAAD4hgAEAAACATwhgAAAAAOATAhgAAAAA+IQABgAAAAA+IYABAAAAgE8IYAAAAADgEwIYAAAAAPiEAAYAAAAAPiGAAQAAAIBPCGAAAAAA4BMCGAAAAAD4hAAGAAAAAD4hgAEAAACATwhgAAAAAOATAhgAAAAA+IQABgAAAAA+IYABAAAAgE8IYAAAAADgEwIYAAAAAPiEAAYAAAAAPiGAAQAAAIBPCGAAAAAA4BMCGAAAAAD4hAAGAAAAAD4hgAEAAACATwhgAAAAAOATAhgAAAAA+IQABgAAAAA+IYABAAAAgE8IYAAAAADgEwIYAAAAAPiEAAYAAAAAPiGAAQAAAIBPCGAAAAAA4BMCGAAAAAD4hAAGAAAAAD4hgAEAAACATwhgAAAAAOATAhgAAAAA+IQABgAAAAA+IYABAAAAgE8IYAAAAADgEwIYAAAAAPiEAAYAAAAAPiGAAQAAAIBPCGAAAAAA4BMCGAAAAAD4hAAGAAAAAD4hgAEAAACATwhgAAAAAOATAhgAAAAA+IQABgAAAAA+IYABAAAAgE8IYAAAAADgEwIYAAAAAPiEAAYAAAAAPiGAAQAAAIBPCGAAAAAA4BMCGAAAAAD4hAAGAAAAAD4hgAEAAACATwhgAAAAAOATAhgAAAAA+IQABgAAAAA+IYABAAAAgE8IYAAAAADgEwIYAAAAAPiEAAYAAAAAPiGAAQAAAIBPCGAAAAAA4BMCGAAAAAD4hAAGAAAAAD4hgAEAAACATwhgAAAAAOATAhgAAAAA+IQABgAAAAA+IYABAAAAgE8IYAAAAADgEwIYAAAAAPiEAAYAAAAAPiGAAQAAAIBPCGAAAAAA4BMCGAAAAAD4hAAGAAAAAD4hgAEAAACATwhgAAAAAOCLv/71/wfVjfX5TGoDnQAAAABJRU5ErkJggg==");
         }

        // QByteArray rdc= qUncompress(rc);

         QImage img;
         img.loadFromData(rc);
         img.save(toPic);
   //  }

 }



     //m_req.setAttribute(QNetworkRequest::HttpStatusCodeAttribute,m_strid);
