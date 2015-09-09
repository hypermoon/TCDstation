#include "reportprintsetting.h"
#include <QHeaderView>

ReportPrintSetting::ReportPrintSetting(QObject *parent) :
    QObject(parent)
{

    m_tableView = new QTableView();
    m_tableModel = new QStandardItemModel(this);
    initTableView();
}

ReportPrintSetting::~ReportPrintSetting()
{
    if(m_tableView)
    {
        delete m_tableView;
        m_tableView = NULL;
    }
}

void ReportPrintSetting::initTableView()
{

    m_tableModel->setHorizontalHeaderItem(0,new QStandardItem(QObject::tr("血管名")));
    m_tableModel->setHorizontalHeaderItem(1,new QStandardItem(QObject::tr("Mean")));
    m_tableModel->setHorizontalHeaderItem(2,new QStandardItem(QObject::tr("Peak")));
    m_tableModel->setHorizontalHeaderItem(3,new QStandardItem(QObject::tr("EDV")));
    m_tableModel->setHorizontalHeaderItem(4,new QStandardItem(QObject::tr("PI")));
    m_tableModel->setHorizontalHeaderItem(5,new QStandardItem(QObject::tr("RI")));
    m_tableModel->setHorizontalHeaderItem(6,new QStandardItem(QObject::tr("S/D")));
    m_tableModel->setHorizontalHeaderItem(7,new QStandardItem(QObject::tr("HR")));
    m_tableView->setModel(m_tableModel);

    m_tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    for (int i=0; i <8; i++)
    {
        //m_tableView->setSelectionModel(i,QHeaderView::Fixed);
        m_tableView->setColumnWidth(i,80);
    }
//    QString str = "56";
//    for(int i=0;i<10;i++)
//    {
//        m_tableModel->setItem(i,0,new QStandardItem("45"));
//        m_tableModel->setItem(i,1,new QStandardItem(str));
//        m_tableModel->setItem(i,2,new QStandardItem(52));
//        m_tableModel->setItem(i,3,new QStandardItem(63));
//        m_tableModel->setItem(i,4,new QStandardItem(34));
//        m_tableModel->setItem(i,5,new QStandardItem(55));
//        m_tableModel->setItem(i,6,new QStandardItem(46));
//        m_tableModel->setItem(i,7,new QStandardItem(67));
//    }
}

void ReportPrintSetting::SetReportForm(QPainter &painter)
{
    //title
    drawPosition(Title,"TCD检查报告单",painter,TEXT,"",25,"SimSun",true);
    //basic info
    drawPosition(Splitter1,"",painter,SPLITTER,"");
    drawPosition(BasicInfoTitle,"基本信息",painter,TEXT,"",15,"SimSun",true);
    drawPosition(MedRecordNo,"病历号:",painter);
    drawPosition(AdmissionNo,"住院号:",painter);
    drawPosition(CheckDate,"检查日期:",painter);
    drawPosition(PatientName,"姓名:",painter);
    drawPosition(Gender,"性别:",painter);
    drawPosition(Age,"年龄:",painter);
    drawPosition(Height,"身高:",painter);
    drawPosition(Weight,"体重:",painter);

    //TCD Screen shot
    drawPosition(TcdTitle,"TCD数据",painter,TEXT,"",15,"SimSun",true);
    drawPosition(Splitter2,"",painter,SPLITTER,"");

//    //TCD Data
//    drawPosition(VesselNameOne,"血管名:",painter,WIDGET,"",15,"SimSun",true);

    //    drawPosition(VesselNameOne,"血管名:",painter);
    //    drawPosition(DataMeanOne,"Mean:",painter);
    //    drawPosition(DataPeakOne,"Peak:",painter);
    //    drawPosition(DataEdvOne,"EDV:",painter);
    //    drawPosition(DataPiOne,"PI:",painter);
    //    drawPosition(DataRiOne,"RI:",painter);
    //    drawPosition(DataSdOne,"S/D:",painter);
    //    drawPosition(DataHrOne,"HR:",painter);

    //    drawPosition(VesselNameTwo,"血管名:",painter);
    //    drawPosition(DataMeanTwo,"Mean:",painter);
    //    drawPosition(DataPeakTwo,"Peak:",painter);
    //    drawPosition(DataEdvTwo,"EDV:",painter);
    //    drawPosition(DataPiTwo,"PI:",painter);
    //    drawPosition(DataRiTwo,"RI:",painter);
    //    drawPosition(DataSdTwo,"S/D:",painter);
    //    drawPosition(DataHrTwo,"HR:",painter);

    //    drawPosition(VesselNameThree,"血管名:",painter);
    //    drawPosition(DataMeanThree,"Mean:",painter);
    //    drawPosition(DataPeakThree,"Peak:",painter);
    //    drawPosition(DataEdvThree,"EDV:",painter);
    //    drawPosition(DataPiThree,"PI:",painter);
    //    drawPosition(DataRiThree,"RI:",painter);
    //    drawPosition(DataSdThree,"S/D:",painter);
    //    drawPosition(DataHrThree,"HR:",painter);

    //    drawPosition(VesselNameFour,"血管名:",painter);
    //    drawPosition(DataMeanFour,"Mean:",painter);
    //    drawPosition(DataPeakFour,"Peak:",painter);
    //    drawPosition(DataEdvFour,"EDV:",painter);
    //    drawPosition(DataPiFour,"PI:",painter);
    //    drawPosition(DataRiFour,"RI:",painter);
    //    drawPosition(DataSdFour,"S/D:",painter);
    //    drawPosition(DataHrFour,"HR:",painter);

    drawPosition(Splitter3,"",painter,SPLITTER,"");
    drawPosition(DiagnoseTitle,"医生诊断",painter,TEXT,"",15,"SimSun",true);
    drawPosition(Signature,"负责医师:",painter);

    QString notice= "此报告仅供临床医生参考,不作证明使用";
    drawPosition(Notice,notice,painter);
}

void ReportPrintSetting::SetReportContent(QPainter &painter)
{ 
    //basic info
    QString recordNO =  m_patientTracker->Data().patient.strChartNumber;
    QString admissionNO = m_patientTracker->Data().patient.strAdmissionNumber;
    QString checkDate = m_patientTracker->Data().patient.strDate;

    QString patientName = m_patientTracker->Data().patient.strName;
    QString gender = m_patientTracker->Data().patient.strGender;
    int age = m_patientTracker->Data().patient.nAge;
    qreal height  = m_patientTracker->Data().patient.qHeight;
    qreal weight  = m_patientTracker->Data().patient.qWeight;

    drawPosition(MedRecordContent,recordNO,painter);
    drawPosition(AdmissionContent,admissionNO,painter);
    drawPosition(CheckDateContent,checkDate,painter);

    drawPosition(NameContent,patientName,painter);
    drawPosition(GenderContent,gender,painter);
    drawPosition(AgeContent,QString::number(age),painter);

    drawPosition(HeightContent,QString::number(height),painter);
    drawPosition(WeightContent,QString::number(weight),painter);

    //tcd data
    QString img[IMGCOUNTS];
    QString vessel[IMGCOUNTS];
    QString mean[IMGCOUNTS];
    QString peak[IMGCOUNTS];
    QString edv[IMGCOUNTS];
    QString pi[IMGCOUNTS];
    QString ri[IMGCOUNTS];
    QString sd[IMGCOUNTS];
    QString hr[IMGCOUNTS];
    QString filePath = m_patientTracker->GetPatientFolderPath();
    for( int i=0; i<IMGCOUNTS; i++)
    {
        img[i] = filePath+"/"+m_patientTracker->Data().data[i].pictureName;
        vessel[i]  = m_patientTracker->Data().data[i].name;
        mean[i] = QString::number(m_patientTracker->Data().data[i].qMean);
        peak[i] = QString::number(m_patientTracker->Data().data[i].qPeak);
        edv[i] = QString::number(m_patientTracker->Data().data[i].qEDV);
        pi[i] = QString::number(m_patientTracker->Data().data[i].qPI);
        ri[i] = QString::number(m_patientTracker->Data().data[i].qRI);
        sd[i] = QString::number(m_patientTracker->Data().data[i].qSD);
        hr[i] = QString::number(m_patientTracker->Data().data[i].qHR);

        //tcd data
        //        drawPosition(VesselValueOne+8*i,vessel[i],painter);
        //        drawPosition(MeanValueOne+8*i,mean[i],painter);
        //        drawPosition(PeakValueOne+8*i,peak[i],painter);
        //        drawPosition(EdvValueOne+8*i,edv[i],painter);
        //        drawPosition(PIValueOne+8*i,pi[i],painter);
        //        drawPosition(RIValueOne+8*i,ri[i],painter);
        //        drawPosition(SDValueOne+8*i,sd[i],painter);
        //        drawPosition(HRValueOne+8*i,hr[i],painter);
        m_tableModel->setItem(i,0,new QStandardItem(vessel[i]));
        m_tableModel->setItem(i,1,new QStandardItem(mean[i]));
        m_tableModel->setItem(i,2,new QStandardItem(peak[i]));
        m_tableModel->setItem(i,3,new QStandardItem(edv[i]));
        m_tableModel->setItem(i,4,new QStandardItem(pi[i]));
        m_tableModel->setItem(i,5,new QStandardItem(ri[i]));
        m_tableModel->setItem(i,6,new QStandardItem(sd[i]));
        m_tableModel->setItem(i,7,new QStandardItem(hr[i]));


        //drawPosition(ImgOne+i,"",painter,IMAGE,":/pic/test.png");
        drawPosition(ImgOne+i,"",painter,IMAGE,img[i]);
    }

    // diagnose

    QString content = m_patientTracker->Data().text.text;
    QString doctorName = m_patientTracker->Data().text.name;
    drawPosition(DiagnoseContent,content,painter,TEXT,"",13,"",false);
    drawPosition(SignatureContent,doctorName,painter);

    //TCD Data
    drawPosition(VesselNameOne,"血管名:",painter,WIDGET,"",15,"SimSun",true);

}

void ReportPrintSetting::SetPatient(PatientTracker *tracker)
{
    m_patientTracker = tracker;
}


void ReportPrintSetting::drawPosition(int type, QString content, QPainter &painter,
                                      int drawType,QString img,
                                      int fontSize, const QString family,
                                      bool bold)
{
    ReportFormDefinition report;
    // QString file("../tcdstation/reportForm.xml");
    QString file("reportForm.xml");
    report.ReadReportContent(file);
    QRectF rectF;
    report.GetPosition(type,rectF);

    QFont font;
    font.setPointSize(fontSize);
    font.setBold(bold);
    font.setFamily(family);

    painter.setFont(font);
    if(drawType == SPLITTER)
    {
        QPoint startPoint(rectF.x(),rectF.y());
        QPoint endPoint(rectF.x()+rectF.width(),rectF.y()+rectF.height());
        painter.drawLine(startPoint,endPoint);
    }
    else if(drawType == TEXT)
    {
        painter.drawText(rectF,Qt::TextWordWrap,content);
    }
    else if(drawType == IMAGE)
    {
        //QImage image(img);
        QPixmap pixmap;
        pixmap.load(img);
        //painter.drawImage(rectF,image);
        painter.drawPixmap(rectF.x(),rectF.y(),rectF.width(),rectF.height(),pixmap);
    }
    else if(drawType == WIDGET)
    {
        QPixmap grabImage;
        QRect rect;
        rect.setSize(QSize(rectF.width(),rectF.height()));
        m_tableView->resize(rect.size());
        grabImage = m_tableView->grab(QRect(0,0,m_tableView->width(),m_tableView->height()));


        grabImage.scaled(rect.size(),Qt::KeepAspectRatio);
        painter.drawPixmap(rectF.x(),rectF.y(),grabImage);
    }

}

