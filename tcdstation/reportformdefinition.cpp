#include "reportformdefinition.h"


#include <QDebug>
#include <QRectF>

ReportFormDefinition::ReportFormDefinition(QObject *parent):
    QObject(parent)
{
    m_currentY = 20;
    m_startXPos = 10;
    m_pageWidth = 793; //  qreal width = printer.logicalDpiX()*(210/25.4);
    m_pageHeight = 1122; //  qreal height= printer.logicalDpiY()*(297/25.4);

    m_imgCount = 4;
    m_titleHeight = m_pageHeight/35;
    m_basicInfoHeight = m_pageHeight/7;
    m_tcdScreenShotHeight = m_pageHeight/5;
    m_tcdDataHeight = m_pageHeight/5;
    m_tcdEachDataHeight =  m_tcdDataHeight/8;
    m_diagnoseHeight = m_pageHeight/8;
    clearVector();
}

void ReportFormDefinition::WriteReportForm()
{
    //QFile file("../tcdstation/reportForm.xml");
    QFile file("reportForm.xml");
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QXmlStreamWriter writer(&file);
        writer.setAutoFormatting(true);
        writer.writeStartDocument();
        writer.writeStartElement("DATA");

        writer.writeStartElement("Title");
        writer.writeTextElement("XPos",QString::number(m_pageWidth/3.0));
        writer.writeTextElement("YPos",QString::number(m_currentY));
        writer.writeTextElement("Width",QString::number(m_pageHeight/3.0));
        writer.writeTextElement("Height",QString::number(30));
        m_currentY += m_titleHeight;

        writer.writeEndElement();


        writeBasicInfoForm(writer);
        writeTCDScreenShot(writer);
        writeTCDDataForm(writer);
        writeDiagnose(writer);
        writeNotice(writer);

        writer.writeEndDocument();
        file.close();
    }
}

void ReportFormDefinition::ReadReportContent(QString &fileName)
{
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QXmlStreamReader reader(&file);
        while(!reader.atEnd())
        {
            reader.readNext();
            if(reader.isStartElement())
            {
                if("Title"== reader.name())
                {
                   // qDebug()<<"Start to read title...";
                    readPosition(reader,m_titleVec,"Title");
                }
                if("splitter1"==reader.name())
                {
                    readPosition(reader,m_splitterOneVec,"splitter1");
                }
                if("BasicInfo" == reader.name())
                {
                   // qDebug()<<"Start to basic Info...";
                    readBasicInfo(reader);
                }
                if("splitter2"==reader.name())
                {
                    readPosition(reader,m_splitterTwoVec,"splitter2");
                }
                if("ScreenShot" == reader.name())
                {
                   // qDebug()<<"Start to read screen shot...";
                    readTCDScreenShot(reader);
                }
                if("TCDData"==reader.name())
                {
                   // qDebug()<<"Start to read TCD data...";
                    readTCDData(reader);
                }
                if("splitter3"==reader.name())
                {
                    readPosition(reader,m_splitterThreeVec,"splitter3");
                }
                if("Diagnose"==reader.name())
                {
                    //qDebug()<<"Start to read diagnose...";
                    readDiagnose(reader);
                }
                if("Notice" == reader.name())
                {
                    readNotice(reader);
                }
            }
        }

    }

}




void ReportFormDefinition::GetPosition(int num,QRectF& rect)
{
    QVector<QString> strVec;
    strVec.clear();
    switch (num) {
    case Title:
        strVec = m_titleVec;
        break;
    case Splitter1:
        strVec = m_splitterOneVec;
        break;
    case Splitter2:
        strVec = m_splitterTwoVec;
        break;
    case Splitter3:
        strVec = m_splitterThreeVec;
        break;
    case BasicInfoTitle:
        strVec = m_basicInfoTitleVec;
        break;
    case MedRecordNo:
        strVec = m_MedRecordNOVec;
        break;
    case AdmissionNo:
        strVec = m_AdmissionNOVec;
        break;
    case CheckDate:
        strVec = m_CheckDateVec;
        break;
    case PatientName:
        strVec = m_NameVec;
        break;
    case Gender:
        strVec = m_GenderVec;
        break;
    case Age:
        strVec = m_AgeVec;
        break;
    case Height:
        strVec = m_heightVec;
        break;
    case Weight:
        strVec = m_weightVec;
        break;
    case TcdTitle:
        strVec = m_screenShotVec;
        break;
    case ImgOne:
        strVec = m_ImgOneVec;
        break;
    case ImgTwo:
        strVec = m_ImgTwoVec;
        break;
    case ImgThree:
        strVec = m_ImgThreeVec;
        break;
    case ImgFour:
        strVec = m_ImgFourVec;
        break;
    case VesselNameOne:
        strVec = m_vesselNameOne;
        break;
    case DataMeanOne:
        strVec = m_dataOneMeanVec;
        break;
    case DataPeakOne:
        strVec = m_dataOnePeakVec;
        break;
    case DataEdvOne:
        strVec = m_dataOneEDVVec;
        break;
    case DataPiOne:
        strVec = m_dataOnePIVec;
        break;
    case DataRiOne:
        strVec = m_dataOneRIVec;
        break;
    case DataSdOne:
        strVec = m_dataOneSDVec;
        break;
    case DataHrOne:
        strVec = m_dataOneHRVec;
        break;
    case VesselNameTwo:
        strVec = m_vesselNameTwo;
        break;
    case DataMeanTwo:
        strVec = m_dataTwoMeanVec;
        break;
    case DataPeakTwo:
        strVec = m_dataTwoPeakVec;
        break;
    case DataEdvTwo:
        strVec = m_dataTwoEDVVec;
        break;
    case DataPiTwo:
        strVec = m_dataTwoPIVec;
        break;
    case DataRiTwo:
        strVec = m_dataTwoRIVec;
        break;
    case DataSdTwo:
        strVec = m_dataTwoSDVec;
        break;
    case DataHrTwo:
        strVec = m_dataTwoHRVec;
        break;
    case VesselNameThree:
        strVec = m_vesselNameThree;
        break;
    case DataMeanThree:
        strVec = m_dataThreeMeanVec;
        break;
    case DataPeakThree:
        strVec = m_dataThreePeakVec;
        break;
    case DataEdvThree:
        strVec = m_dataThreeEDVVec;
        break;
    case DataPiThree:
        strVec = m_dataThreePIVec;
        break;
    case DataRiThree:
        strVec = m_dataThreeRIVec;
        break;
    case DataSdThree:
        strVec = m_dataThreeSDVec;
        break;
    case DataHrThree:
        strVec = m_dataThreeHRVec;
        break;
    case VesselNameFour:
        strVec = m_vesselNameFour;
        break;
    case DataMeanFour:
        strVec = m_dataFourMeanVec;
        break;
    case DataPeakFour:
        strVec = m_dataFourPeakVec;
        break;
    case DataEdvFour:
        strVec = m_dataFourEDVVec;
        break;
    case DataPiFour:
        strVec = m_dataFourPIVec;
        break;
    case DataRiFour:
        strVec = m_dataFourRIVec;
        break;
    case DataSdFour:
        strVec = m_dataFourSDVec;
        break;
    case DataHrFour:
        strVec = m_dataFourHRVec;
        break;
    case DiagnoseTitle:
        strVec = m_diagnoseVec;
        break;
    case Signature:
        strVec = m_signatureVec;
        break;
    case DiagnoseContent:
        strVec = m_contentVec;
        break;
    case SignatureContent:
        strVec = m_sigContentVec;
        break;
    case MedRecordContent:
        strVec = m_MedRecordNOContentVec;
        break;
    case AdmissionContent:
        strVec = m_AdmissionNOContentVec;
        break;
    case CheckDateContent:
        strVec = m_CheckDateContentVec;
        break;
    case NameContent:
        strVec = m_NameContentVec;
        break;
    case GenderContent:
        strVec = m_GenderContentVec;
        break;
    case AgeContent:
        strVec = m_AgeContentVec;
        break;
    case HeightContent:
        strVec = m_heightContentVec;
        break;
    case WeightContent:
        strVec = m_weightContentVec;
        break;
    case VesselValueOne:
        strVec = m_vesselValueOne;
        break;
    case VesselValueTwo:
        strVec = m_vesselValueTwo;
        break;
    case VesselValueThree:
         strVec = m_vesselValueThree;
         break;
    case VesselValueFour:
        strVec = m_vesselValueFour;
        break;
    case MeanValueOne:
        strVec = m_meanOneContent;
        break;
    case PeakValueOne:
        strVec = m_peakOneContent;
        break;
    case EdvValueOne:
        strVec = m_edvOneContent;
        break;
    case PIValueOne:
        strVec = m_piOneContent;
        break;
    case RIValueOne:
        strVec = m_riOneContent;
        break;
    case SDValueOne:
        strVec = m_sdOneContent;
        break;
    case HRValueOne:
        strVec = m_hrOneContent;
        break;
    case MeanValueTwo:
        strVec = m_meanTwoContent;
        break;
    case PeakValueTwo:
        strVec = m_peakTwoContent;
        break;
    case EdvValueTwo:
        strVec = m_edvTwoContent;
        break;
    case PIValueTwo:
        strVec = m_piTwoContent;
        break;
    case RIValueTwo:
        strVec = m_riTwoContent;
        break;
    case SDValueTwo:
        strVec = m_sdTwoContent;
        break;
    case HRValueTwo:
        strVec = m_hrTwoContent;
        break;
    case MeanValueThree:
        strVec = m_meanThreeContent;
        break;
    case PeakValueThree:
        strVec = m_peakThreeContent;
        break;
    case EdvValueThree:
        strVec = m_edvThreeContent;
        break;
    case PIValueThree:
        strVec = m_piThreeContent;
        break;
    case RIValueThree:
        strVec = m_riThreeContent;
        break;
    case SDValueThree:
        strVec = m_sdThreeContent;
        break;
    case HRValueThree:
        strVec = m_hrThreeContent;
        break;
    case MeanValueFour:
        strVec = m_meanFourContent;
        break;
    case PeakValueFour:
        strVec = m_peakFourContent;
        break;
    case EdvValueFour:
        strVec = m_edvFourContent;
        break;
    case PIValueFour:
        strVec = m_piFourContent;
        break;
    case RIValueFour:
        strVec = m_riFourContent;
        break;
    case SDValueFour:
        strVec = m_sdFourContent;
        break;
    case HRValueFour:
        strVec = m_hrFourContent;
        break;
    case Notice:
        strVec = m_noticeVec;
        break;
    default:
        break;
    }

    //qDebug()<<strVec.size()<<endl;
    if(strVec.size() == 4)
    {
        rect.setX(strVec[0].toFloat());
        rect.setY(strVec[1].toFloat());
        rect.setWidth(strVec[2].toFloat());
        rect.setHeight(strVec[3].toFloat());
    }
    else
    {
        qDebug()<<"Error!"<<endl;
    }
}

void ReportFormDefinition::writeBasicInfoForm(QXmlStreamWriter &writer)
{
    //Splitter
    writer.writeStartElement("splitter1");
    writer.writeTextElement("XPos",QString::number(m_startXPos));
    writer.writeTextElement("YPos",QString::number(m_currentY+15));
    writer.writeTextElement("Width",QString::number(m_pageWidth-40));
    writer.writeTextElement("Height",QString::number(2));
    writer.writeEndElement();

    writer.writeStartElement("BasicInfo");
    writer.writeStartElement("title");
    writer.writeTextElement("XPos",QString::number(m_startXPos));
    writer.writeTextElement("YPos",QString::number(m_currentY+35));
    writer.writeTextElement("Width",QString::number(m_pageWidth - m_startXPos*2));
    writer.writeTextElement("Height",QString::number(m_basicInfoHeight));
    writer.writeEndElement();

    //Medical Record NO
    writer.writeStartElement("MedRecordNO");
    writer.writeTextElement("XPos",QString::number(m_startXPos+20));
    writer.writeTextElement("YPos",QString::number(m_currentY+70));
    writer.writeTextElement("Width",QString::number((m_pageWidth - m_startXPos*2)/3.0-80));
    writer.writeTextElement("Height",QString::number(25));
    writer.writeEndElement();

    writer.writeStartElement("MedRecordNOContent");
    writer.writeTextElement("XPos",QString::number(m_startXPos+90));
    writer.writeTextElement("YPos",QString::number(m_currentY+70));
    writer.writeTextElement("Width",QString::number(80));
    writer.writeTextElement("Height",QString::number(25));
    writer.writeEndElement();

    //Admission NO
    writer.writeStartElement("AdmissionNO");
    writer.writeTextElement("XPos",QString::number(m_startXPos+30+(m_pageWidth - m_startXPos*2)/3.0));
    writer.writeTextElement("YPos",QString::number(m_currentY+70));
    writer.writeTextElement("Width",QString::number((m_pageWidth - m_startXPos*2)/3.0-80));
    writer.writeTextElement("Height",QString::number(25));
    writer.writeEndElement();

    writer.writeStartElement("AdmissionNOContent");
    writer.writeTextElement("XPos",QString::number(m_startXPos+100+(m_pageWidth - m_startXPos*2)/3.0));
    writer.writeTextElement("YPos",QString::number(m_currentY+70));
    writer.writeTextElement("Width",QString::number(80));
    writer.writeTextElement("Height",QString::number(25));
    writer.writeEndElement();


    //Check Date
    writer.writeStartElement("CheckDate");
    writer.writeTextElement("XPos",QString::number(m_startXPos+30+(m_pageWidth - m_startXPos*2)*2/3.0));
    writer.writeTextElement("YPos",QString::number(m_currentY+70));
    writer.writeTextElement("Width",QString::number((m_pageWidth - m_startXPos*2)/3.0-80));
    writer.writeTextElement("Height",QString::number(25));
    writer.writeEndElement();

    writer.writeStartElement("CheckDateContent");
    writer.writeTextElement("XPos",QString::number(m_startXPos+130+(m_pageWidth - m_startXPos*2)*2/3.0));
    writer.writeTextElement("YPos",QString::number(m_currentY+70));
    writer.writeTextElement("Width",QString::number(120));
    writer.writeTextElement("Height",QString::number(25));
    writer.writeEndElement();


    //Name
    writer.writeStartElement("Name");
    writer.writeTextElement("XPos",QString::number(m_startXPos+20));
    writer.writeTextElement("YPos",QString::number(m_currentY+110));
    writer.writeTextElement("Width",QString::number((m_pageWidth - m_startXPos*2)/3.0-80));
    writer.writeTextElement("Height",QString::number(25));
    writer.writeEndElement();

    writer.writeStartElement("NameContent");
    writer.writeTextElement("XPos",QString::number(m_startXPos+90));
    writer.writeTextElement("YPos",QString::number(m_currentY+110));
    writer.writeTextElement("Width",QString::number(80));
    writer.writeTextElement("Height",QString::number(25));
    writer.writeEndElement();

    //Gender
    writer.writeStartElement("Gender");
    writer.writeTextElement("XPos",QString::number(m_startXPos+30+(m_pageWidth - m_startXPos*2)/3.0));
    writer.writeTextElement("YPos",QString::number(m_currentY+110));
    writer.writeTextElement("Width",QString::number((m_pageWidth - m_startXPos*2)/3.0-80));
    writer.writeTextElement("Height",QString::number(25));
    writer.writeEndElement();

    writer.writeStartElement("GenderContent");
    writer.writeTextElement("XPos",QString::number(m_startXPos+100+(m_pageWidth - m_startXPos*2)/3.0));
    writer.writeTextElement("YPos",QString::number(m_currentY+110));
    writer.writeTextElement("Width",QString::number(80));
    writer.writeTextElement("Height",QString::number(25));
    writer.writeEndElement();


    //Age
    writer.writeStartElement("Age");
    writer.writeTextElement("XPos",QString::number(m_startXPos+30+(m_pageWidth - m_startXPos*2)*2/3.0));
    writer.writeTextElement("YPos",QString::number(m_currentY+110));
    writer.writeTextElement("Width",QString::number((m_pageWidth - m_startXPos*2)/3.0-80));
    writer.writeTextElement("Height",QString::number(25));
    writer.writeEndElement();

    writer.writeStartElement("AgeContent");
    writer.writeTextElement("XPos",QString::number(m_startXPos+130+(m_pageWidth - m_startXPos*2)*2/3.0));
    writer.writeTextElement("YPos",QString::number(m_currentY+110));
    writer.writeTextElement("Width",QString::number(80));
    writer.writeTextElement("Height",QString::number(25));
    writer.writeEndElement();


    //Body Height
    writer.writeStartElement("BodyHeight");
    writer.writeTextElement("XPos",QString::number(m_startXPos+20));
    writer.writeTextElement("YPos",QString::number(m_currentY+150));
    writer.writeTextElement("Width",QString::number((m_pageWidth - m_startXPos*2)/3.0-80));
    writer.writeTextElement("Height",QString::number(25));
    writer.writeEndElement();

    writer.writeStartElement("BodyHeightContent");
    writer.writeTextElement("XPos",QString::number(m_startXPos+90));
    writer.writeTextElement("YPos",QString::number(m_currentY+150));
    writer.writeTextElement("Width",QString::number(80));
    writer.writeTextElement("Height",QString::number(25));
    writer.writeEndElement();


    //Body Weight
    writer.writeStartElement("BodyWeight");
    writer.writeTextElement("XPos",QString::number(m_startXPos+30+(m_pageWidth - m_startXPos*2)/3.0));
    writer.writeTextElement("YPos",QString::number(m_currentY+150));
    writer.writeTextElement("Width",QString::number((m_pageWidth - m_startXPos*2)/3.0-80));
    writer.writeTextElement("Height",QString::number(25));
    writer.writeEndElement();

    writer.writeStartElement("BodyWeightContent");
    writer.writeTextElement("XPos",QString::number(m_startXPos+90+(m_pageWidth - m_startXPos*2)/3.0));
    writer.writeTextElement("YPos",QString::number(m_currentY+150));
    writer.writeTextElement("Width",QString::number(80));
    writer.writeTextElement("Height",QString::number(25));
    writer.writeEndElement();


    writer.writeEndElement();
    m_currentY += m_basicInfoHeight;
}

void ReportFormDefinition::writeTCDScreenShot(QXmlStreamWriter &writer)
{
    //Splitter
    writer.writeStartElement("splitter2");
    writer.writeTextElement("XPos",QString::number(m_startXPos));
    writer.writeTextElement("YPos",QString::number(m_currentY+30));
    writer.writeTextElement("Width",QString::number(m_pageWidth-40));
    writer.writeTextElement("Height",QString::number(2));
    writer.writeEndElement();

    writer.writeStartElement("ScreenShot");
    writer.writeStartElement("title");
    writer.writeTextElement("XPos",QString::number(m_startXPos));
    writer.writeTextElement("YPos",QString::number(m_currentY+60));
    writer.writeTextElement("Width",QString::number(m_pageWidth/2.0));
    writer.writeTextElement("Height",QString::number(30));
    writer.writeEndElement();

    //Screen Shot
    for(int i=0; i<m_imgCount; i++)
    {
        QString startElem;
        switch (i) {
        case 0:
            startElem = "ImgOne";
            break;
        case 1:
            startElem = "ImgTwo";
            break;
        case 2:
            startElem = "ImgThree";
            break;
        case 3:
            startElem = "ImgFour";
            break;
        default:
            break;
        }
        writer.writeStartElement(startElem);
        writer.writeTextElement("XPos",QString::number(m_startXPos-5+ ((m_pageWidth-2*m_startXPos)*i/m_imgCount)));
        writer.writeTextElement("YPos",QString::number(m_currentY+100));
        writer.writeTextElement("Width",QString::number((m_pageWidth-2*m_startXPos)/m_imgCount-10));
        writer.writeTextElement("Height",QString::number(m_tcdScreenShotHeight));
        writer.writeEndElement();
    }


    writer.writeEndElement();
    m_currentY += m_tcdScreenShotHeight;
}

void ReportFormDefinition::writeTCDDataForm(QXmlStreamWriter &writer)
{
    writer.writeStartElement("TCDData");
    writer.writeStartElement("VesselName");
    writer.writeTextElement("XPos",QString::number(m_startXPos+20));
    writer.writeTextElement("YPos",QString::number(m_currentY+80+m_tcdEachDataHeight));
    writer.writeTextElement("Width",QString::number(m_pageWidth-150));
    writer.writeTextElement("Height",QString::number(m_tcdDataHeight));
    writer.writeEndElement();

//    for( int i = 0; i<m_imgCount; i++)
//    {
//        QString startElem;
//        switch (i) {
//        case 0:
//            startElem = "TCDDataOne";
//            break;
//        case 1:
//            startElem = "TCDDataTwo";
//            break;
//        case 2:
//            startElem = "TCDDataThree";
//            break;
//        case 3:
//            startElem = "TCDDataFour";
//            break;
//        default:
//            break;
//        }

//        writer.writeStartElement(startElem);
//        //vessel name
//        writer.writeStartElement("VesselName");
//        writer.writeTextElement("XPos",QString::number(m_startXPos+(m_pageWidth/m_imgCount)*i));
//        writer.writeTextElement("YPos",QString::number(m_currentY+80+m_tcdEachDataHeight));
//        writer.writeTextElement("Width",QString::number(m_pageWidth-100));
//        writer.writeTextElement("Height",QString::number(m_tcdDataHeight));
//        writer.writeEndElement();

//        writer.writeStartElement("VesselValue");
//        writer.writeTextElement("XPos",QString::number(m_startXPos+70+(m_pageWidth/m_imgCount)*i));
//        writer.writeTextElement("YPos",QString::number(m_currentY+80+m_tcdEachDataHeight));
//        writer.writeTextElement("Width",QString::number(100));
//        writer.writeTextElement("Height",QString::number(m_tcdEachDataHeight));
//        writer.writeEndElement();

//        //mean value
//        writer.writeStartElement("Mean");
//        writer.writeTextElement("XPos",QString::number(m_startXPos+(m_pageWidth/m_imgCount)*i));
//        writer.writeTextElement("YPos",QString::number(m_currentY+80+m_tcdEachDataHeight*2));
//        writer.writeTextElement("Width",QString::number(m_pageWidth/m_imgCount-100));
//        writer.writeTextElement("Height",QString::number(m_tcdEachDataHeight));
//        writer.writeEndElement();

//        writer.writeStartElement("MeanValue");
//        writer.writeTextElement("XPos",QString::number(m_startXPos+50+(m_pageWidth/m_imgCount)*i));
//        writer.writeTextElement("YPos",QString::number(m_currentY+80+m_tcdEachDataHeight*2));
//        writer.writeTextElement("Width",QString::number(100));
//        writer.writeTextElement("Height",QString::number(m_tcdEachDataHeight));
//        writer.writeEndElement();


//        //peak value
//        writer.writeStartElement("Peak");
//        writer.writeTextElement("XPos",QString::number(m_startXPos+(m_pageWidth/m_imgCount)*i));
//        writer.writeTextElement("YPos",QString::number(m_currentY+80+m_tcdEachDataHeight*3));
//        writer.writeTextElement("Width",QString::number(m_pageWidth/m_imgCount-100));
//        writer.writeTextElement("Height",QString::number(m_tcdEachDataHeight));
//        writer.writeEndElement();

//        writer.writeStartElement("PeakValue");
//        writer.writeTextElement("XPos",QString::number(m_startXPos+50+(m_pageWidth/m_imgCount)*i));
//        writer.writeTextElement("YPos",QString::number(m_currentY+80+m_tcdEachDataHeight*3));
//        writer.writeTextElement("Width",QString::number(100));
//        writer.writeTextElement("Height",QString::number(m_tcdEachDataHeight));
//        writer.writeEndElement();


//        //EDV value
//        writer.writeStartElement("EDV");
//        writer.writeTextElement("XPos",QString::number(m_startXPos+(m_pageWidth/m_imgCount)*i));
//        writer.writeTextElement("YPos",QString::number(m_currentY+80+m_tcdEachDataHeight*4));
//        writer.writeTextElement("Width",QString::number(m_pageWidth/m_imgCount-100));
//        writer.writeTextElement("Height",QString::number(m_tcdEachDataHeight));
//        writer.writeEndElement();

//        writer.writeStartElement("EDVValue");
//        writer.writeTextElement("XPos",QString::number(m_startXPos+50+(m_pageWidth/m_imgCount)*i));
//        writer.writeTextElement("YPos",QString::number(m_currentY+80+m_tcdEachDataHeight*4));
//        writer.writeTextElement("Width",QString::number(100));
//        writer.writeTextElement("Height",QString::number(m_tcdEachDataHeight));
//        writer.writeEndElement();


//        //PI value
//        writer.writeStartElement("PI");
//        writer.writeTextElement("XPos",QString::number(m_startXPos+(m_pageWidth/m_imgCount)*i));
//        writer.writeTextElement("YPos",QString::number(m_currentY+80+m_tcdEachDataHeight*5));
//        writer.writeTextElement("Width",QString::number(m_pageWidth/m_imgCount-100));
//        writer.writeTextElement("Height",QString::number(m_tcdEachDataHeight));
//        writer.writeEndElement();

//        writer.writeStartElement("PIValue");
//        writer.writeTextElement("XPos",QString::number(m_startXPos+50+(m_pageWidth/m_imgCount)*i));
//        writer.writeTextElement("YPos",QString::number(m_currentY+80+m_tcdEachDataHeight*5));
//        writer.writeTextElement("Width",QString::number(100));
//        writer.writeTextElement("Height",QString::number(m_tcdEachDataHeight));
//        writer.writeEndElement();

//        //RI value
//        writer.writeStartElement("RI");
//        writer.writeTextElement("XPos",QString::number(m_startXPos+(m_pageWidth/m_imgCount)*i));
//        writer.writeTextElement("YPos",QString::number(m_currentY+80+m_tcdEachDataHeight*6));
//        writer.writeTextElement("Width",QString::number(m_pageWidth/m_imgCount-100));
//        writer.writeTextElement("Height",QString::number(m_tcdEachDataHeight));
//        writer.writeEndElement();

//        writer.writeStartElement("RIValue");
//        writer.writeTextElement("XPos",QString::number(m_startXPos+50+(m_pageWidth/m_imgCount)*i));
//        writer.writeTextElement("YPos",QString::number(m_currentY+80+m_tcdEachDataHeight*6));
//        writer.writeTextElement("Width",QString::number(100));
//        writer.writeTextElement("Height",QString::number(m_tcdEachDataHeight));
//        writer.writeEndElement();

//        //SD value
//        writer.writeStartElement("SD");
//        writer.writeTextElement("XPos",QString::number(m_startXPos+(m_pageWidth/m_imgCount)*i));
//        writer.writeTextElement("YPos",QString::number(m_currentY+80+m_tcdEachDataHeight*7));
//        writer.writeTextElement("Width",QString::number(m_pageWidth/m_imgCount-100));
//        writer.writeTextElement("Height",QString::number(m_tcdEachDataHeight));
//        writer.writeEndElement();

//        writer.writeStartElement("SDValue");
//        writer.writeTextElement("XPos",QString::number(m_startXPos+50+(m_pageWidth/m_imgCount)*i));
//        writer.writeTextElement("YPos",QString::number(m_currentY+80+m_tcdEachDataHeight*7));
//        writer.writeTextElement("Width",QString::number(100));
//        writer.writeTextElement("Height",QString::number(m_tcdEachDataHeight));
//        writer.writeEndElement();

//        //HR value
//        writer.writeStartElement("HR");
//        writer.writeTextElement("XPos",QString::number(m_startXPos+(m_pageWidth/m_imgCount)*i));
//        writer.writeTextElement("YPos",QString::number(m_currentY+80+m_tcdEachDataHeight*8));
//        writer.writeTextElement("Width",QString::number(m_pageWidth/m_imgCount-100));
//        writer.writeTextElement("Height",QString::number(m_tcdEachDataHeight));
//        writer.writeEndElement();

//        writer.writeStartElement("HRValue");
//        writer.writeTextElement("XPos",QString::number(m_startXPos+50+(m_pageWidth/m_imgCount)*i));
//        writer.writeTextElement("YPos",QString::number(m_currentY+80+m_tcdEachDataHeight*8));
//        writer.writeTextElement("Width",QString::number(100));
//        writer.writeTextElement("Height",QString::number(m_tcdEachDataHeight));
//        writer.writeEndElement();

       // writer.writeEndElement();
   // }


   writer.writeEndElement();
    m_currentY += m_tcdDataHeight;
}

void ReportFormDefinition::writeDiagnose(QXmlStreamWriter &writer)
{
    //Splitter
    writer.writeStartElement("splitter3");
    writer.writeTextElement("XPos",QString::number(m_startXPos));
    writer.writeTextElement("YPos",QString::number(m_currentY+120));
    writer.writeTextElement("Width",QString::number(m_pageWidth-20));
    writer.writeTextElement("Height",QString::number(2));
    writer.writeEndElement();

    writer.writeStartElement("Diagnose");
    writer.writeStartElement("title");
    writer.writeTextElement("XPos",QString::number(m_startXPos));
    writer.writeTextElement("YPos",QString::number(m_currentY+130));
    writer.writeTextElement("Width",QString::number(m_pageWidth/2.0));
    writer.writeTextElement("Height",QString::number(20));
    writer.writeEndElement();

    writer.writeStartElement("Content");
    writer.writeTextElement("XPos",QString::number(m_startXPos+10));
    writer.writeTextElement("YPos",QString::number(m_currentY+160));
    writer.writeTextElement("Width",QString::number(m_pageWidth-50));
    writer.writeTextElement("Height",QString::number(m_diagnoseHeight));
    writer.writeEndElement();

    m_currentY += m_diagnoseHeight;

    writer.writeStartElement("Signature");
    writer.writeTextElement("XPos",QString::number(m_pageWidth-240));
    writer.writeTextElement("YPos",QString::number(m_currentY+m_diagnoseHeight+35));
    writer.writeTextElement("Width",QString::number(100));
    writer.writeTextElement("Height",QString::number(20));
    writer.writeEndElement();

    writer.writeStartElement("SignatureContent");
    writer.writeTextElement("XPos",QString::number(m_pageWidth-140));
    writer.writeTextElement("YPos",QString::number(m_currentY+m_diagnoseHeight+55));
    writer.writeTextElement("Width",QString::number(100));
    writer.writeTextElement("Height",QString::number(20));
    writer.writeEndElement();

    writer.writeEndElement();


}

void ReportFormDefinition::writeNotice(QXmlStreamWriter &writer)
{
    writer.writeStartElement("Notice");
    writer.writeTextElement("XPos",QString::number(m_startXPos+20));
    writer.writeTextElement("YPos",QString::number(m_currentY+220));
    writer.writeTextElement("Width",QString::number(m_pageWidth - m_startXPos*2));
    writer.writeTextElement("Height",QString::number(25));
    writer.writeEndElement();
}


void ReportFormDefinition::readBasicInfo(QXmlStreamReader &reader)
{
    readPosition(reader,m_basicInfoTitleVec,"title");
    readPosition(reader,m_MedRecordNOVec,"MedRecordNO");
    readPosition(reader,m_MedRecordNOContentVec,"MedRecordNOContent");
    readPosition(reader,m_AdmissionNOVec,"AdmissionNO");
    readPosition(reader,m_AdmissionNOContentVec,"AdmissionNOContent");
    readPosition(reader,m_CheckDateVec,"CheckDate");
    readPosition(reader,m_CheckDateContentVec,"CheckDateContent");
    readPosition(reader,m_NameVec,"Name");
    readPosition(reader,m_NameContentVec,"NameContent");
    readPosition(reader,m_GenderVec,"Gender");
    readPosition(reader,m_GenderContentVec,"GenderContent");
    readPosition(reader,m_AgeVec,"Age");
    readPosition(reader,m_AgeContentVec,"AgeContent");
    readPosition(reader,m_heightVec,"BodyHeight");
    readPosition(reader,m_heightContentVec,"BodyHeightContent");
    readPosition(reader,m_weightVec,"BodyWeight");
    readPosition(reader,m_weightContentVec,"BodyWeightContent");
}

void ReportFormDefinition::readTCDScreenShot(QXmlStreamReader &reader)
{
    readPosition(reader,m_screenShotVec,"title");

    readPosition(reader,m_ImgOneVec,"ImgOne");
    readPosition(reader,m_ImgTwoVec,"ImgTwo");
    readPosition(reader,m_ImgThreeVec,"ImgThree");
    readPosition(reader,m_ImgFourVec,"ImgFour");
}

void ReportFormDefinition::readTCDData(QXmlStreamReader &reader)
{
//    readTCDDataOne(reader);
//    readTCDDataTwo(reader);
//    readTCDDataThree(reader);
//    readTCDDataFour(reader);
    readPosition(reader,m_vesselNameOne,"VesselName");
}

void ReportFormDefinition::readTCDDataOne(QXmlStreamReader &reader)
{
    readPosition(reader,m_vesselNameOne,"VesselName");
    readPosition(reader,m_vesselValueOne,"VesselValue");

    readPosition(reader,m_dataOneMeanVec,"Mean");
    readPosition(reader,m_meanOneContent,"MeanValue");

    readPosition(reader,m_dataOnePeakVec,"Peak");
    readPosition(reader,m_peakOneContent,"PeakValue");

    readPosition(reader,m_dataOneEDVVec,"EDV");
    readPosition(reader,m_edvOneContent,"EDVValue");

    readPosition(reader,m_dataOnePIVec,"PI");
    readPosition(reader,m_piOneContent,"PIValue");

    readPosition(reader,m_dataOneRIVec,"RI");
    readPosition(reader,m_riOneContent,"RIValue");

    readPosition(reader,m_dataOneSDVec,"SD");
    readPosition(reader,m_sdOneContent,"SDValue");

    readPosition(reader,m_dataOneHRVec,"HR");
    readPosition(reader,m_hrOneContent,"HRValue");
}

void ReportFormDefinition::readTCDDataTwo(QXmlStreamReader &reader)
{
    readPosition(reader,m_vesselNameTwo,"VesselName");
    readPosition(reader,m_vesselValueTwo,"VesselValue");

    readPosition(reader,m_dataTwoMeanVec,"Mean");
    readPosition(reader,m_meanTwoContent,"MeanValue");

    readPosition(reader,m_dataTwoPeakVec,"Peak");
    readPosition(reader,m_peakTwoContent,"PeakValue");

    readPosition(reader,m_dataTwoEDVVec,"EDV");
    readPosition(reader,m_edvTwoContent,"EDVValue");

    readPosition(reader,m_dataTwoPIVec,"PI");
    readPosition(reader,m_piTwoContent,"PIValue");

    readPosition(reader,m_dataTwoRIVec,"RI");
    readPosition(reader,m_riTwoContent,"RIValue");

    readPosition(reader,m_dataTwoSDVec,"SD");
    readPosition(reader,m_sdTwoContent,"SDValue");

    readPosition(reader,m_dataTwoHRVec,"HR");
    readPosition(reader,m_hrTwoContent,"HRValue");
}

void ReportFormDefinition::readTCDDataThree(QXmlStreamReader &reader)
{
    readPosition(reader,m_vesselNameThree,"VesselName");
    readPosition(reader,m_vesselValueThree,"VesselValue");

    readPosition(reader,m_dataThreeMeanVec,"Mean");
    readPosition(reader,m_meanThreeContent,"MeanValue");

    readPosition(reader,m_dataThreePeakVec,"Peak");
    readPosition(reader,m_peakThreeContent,"PeakValue");

    readPosition(reader,m_dataThreeEDVVec,"EDV");
    readPosition(reader,m_edvThreeContent,"EDVValue");

    readPosition(reader,m_dataThreePIVec,"PI");
    readPosition(reader,m_piThreeContent,"PIValue");

    readPosition(reader,m_dataThreeRIVec,"RI");
    readPosition(reader,m_riThreeContent,"RIValue");

    readPosition(reader,m_dataThreeSDVec,"SD");
    readPosition(reader,m_sdThreeContent,"SDValue");

    readPosition(reader,m_dataThreeHRVec,"HR");
    readPosition(reader,m_hrThreeContent,"HRValue");
}

void ReportFormDefinition::readTCDDataFour(QXmlStreamReader &reader)
{
    readPosition(reader,m_vesselNameFour,"VesselName");
    readPosition(reader,m_vesselValueFour,"VesselValue");

    readPosition(reader,m_dataFourMeanVec,"Mean");
    readPosition(reader,m_meanFourContent,"MeanValue");

    readPosition(reader,m_dataFourPeakVec,"Peak");
    readPosition(reader,m_peakFourContent,"PeakValue");

    readPosition(reader,m_dataFourEDVVec,"EDV");
    readPosition(reader,m_edvFourContent,"EDVValue");

    readPosition(reader,m_dataFourPIVec,"PI");
    readPosition(reader,m_piFourContent,"PIValue");

    readPosition(reader,m_dataFourRIVec,"RI");
    readPosition(reader,m_riFourContent,"RIValue");

    readPosition(reader,m_dataFourSDVec,"SD");
    readPosition(reader,m_sdFourContent,"SDValue");

    readPosition(reader,m_dataFourHRVec,"HR");
    readPosition(reader,m_hrFourContent,"HRValue");
}

void ReportFormDefinition::readDiagnose(QXmlStreamReader &reader)
{
    readPosition(reader,m_diagnoseVec,"title");
    readPosition(reader,m_contentVec,"Content");
    readPosition(reader,m_signatureVec,"Signature");
    readPosition(reader,m_sigContentVec,"SignatureContent");
}

void ReportFormDefinition::readNotice(QXmlStreamReader &reader)
{
   readPosition(reader,m_noticeVec,"Notice");
}

void ReportFormDefinition::readPosition(QXmlStreamReader &reader, QVector<QString> &vec, QString startName)
{
    //qDebug()<<"Start to read "<< startName;

    while(!reader.atEnd())
    {
        reader.readNext();
        if(reader.isStartElement())
        {
            if("XPos"==reader.name())
            {
                // qDebug()<<reader.readElementText();
                vec.append(reader.readElementText());
            }
            if("YPos"==reader.name())
            {
                // qDebug()<<reader.readElementText();
                vec.append(reader.readElementText());
            }
            if("Width"==reader.name())
            {
                // qDebug()<<reader.readElementText();
                vec.append(reader.readElementText());
            }
            if("Height"==reader.name())
            {
                //  qDebug()<<reader.readElementText();
                vec.append(reader.readElementText());
            }
        }
        if(reader.isEndElement())
        {
            if(startName==reader.name())
            {
                QVector<QString>::iterator iter = vec.begin();
                //qDebug()<<startName;
                for(;iter!=vec.end();iter++)
                {
                   // qDebug()<<*iter;
                }
               // qDebug()<<"At the end of "<< startName<<endl;
                break;
            }
        }
    }
}

void ReportFormDefinition::clearVector()
{
    //title
    m_titleVec.clear();

    //basic info
    m_basicInfoTitleVec.clear();
    m_MedRecordNOVec.clear();
    m_AdmissionNOVec.clear();
    m_CheckDateVec.clear();
    m_NameVec.clear();
    m_GenderVec.clear();
    m_AgeVec.clear();
    m_heightVec.clear();
    m_weightVec.clear();

    //Screen shot
    m_screenShotVec.clear();
    m_ImgOneVec.clear();
    m_ImgTwoVec.clear();
    m_ImgThreeVec.clear();

    //TCD data
    m_dataOneMeanVec.clear();
    m_dataOnePeakVec.clear();
    m_dataOneEDVVec.clear();
    m_dataOnePIVec.clear();
    m_dataOneRIVec.clear();
    m_dataOneSDVec.clear();
    m_dataOneHRVec.clear();

    m_dataTwoMeanVec.clear();
    m_dataTwoPeakVec.clear();
    m_dataTwoEDVVec.clear();
    m_dataTwoPIVec.clear();
    m_dataTwoRIVec.clear();
    m_dataTwoSDVec.clear();
    m_dataTwoHRVec.clear();

    m_dataThreeMeanVec.clear();
    m_dataThreePeakVec.clear();
    m_dataThreeEDVVec.clear();
    m_dataThreePIVec.clear();
    m_dataThreeRIVec.clear();
    m_dataThreeSDVec.clear();
    m_dataThreeHRVec.clear();

    m_dataFourMeanVec.clear();
    m_dataFourPeakVec.clear();
    m_dataFourEDVVec.clear();
    m_dataFourPIVec.clear();
    m_dataFourRIVec.clear();
    m_dataFourSDVec.clear();
    m_dataFourHRVec.clear();

    m_diagnoseVec.clear();
    m_contentVec.clear();
    m_signatureVec.clear();
    m_splitterOneVec.clear();
    m_splitterThreeVec.clear();
    m_splitterTwoVec.clear();

    m_sigContentVec.clear();
    m_MedRecordNOContentVec.clear();
    m_AdmissionNOContentVec.clear();
    m_NameContentVec.clear();
    m_GenderContentVec.clear();
    m_AgeContentVec.clear();
    m_CheckDateContentVec.clear();
    m_heightContentVec.clear();
    m_weightContentVec.clear();

    m_meanOneContent.clear();
    m_peakOneContent.clear();
    m_edvOneContent.clear();
    m_piOneContent.clear();
    m_riOneContent.clear();
    m_sdOneContent.clear();
    m_hrOneContent.clear();

    m_meanTwoContent.clear();
    m_peakTwoContent.clear();
    m_edvTwoContent.clear();
    m_piTwoContent.clear();
    m_riTwoContent.clear();
    m_sdTwoContent.clear();
    m_hrTwoContent.clear();

    m_meanThreeContent.clear();
    m_peakThreeContent.clear();
    m_edvThreeContent.clear();
    m_piThreeContent.clear();
    m_riThreeContent.clear();
    m_sdThreeContent.clear();
    m_hrThreeContent.clear();

    m_meanFourContent.clear();
    m_peakFourContent.clear();
    m_edvFourContent.clear();
    m_piFourContent.clear();
    m_riFourContent.clear();
    m_sdFourContent.clear();
    m_hrFourContent.clear();

    m_vesselNameOne.clear();
    m_vesselNameTwo.clear();
    m_vesselNameThree.clear();
    m_vesselNameFour.clear();

    m_vesselValueOne.clear();
    m_vesselValueTwo.clear();
    m_vesselValueThree.clear();
    m_vesselValueFour.clear();

    m_noticeVec.clear();
}
