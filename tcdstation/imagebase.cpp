#include "imagebase.h"
#include <QRgb>
#include <QFile>
#include <qmath.h>
#include <QDebug>

ImageBase::ImageBase(QObject *parent) :
    QObject(parent)
{
    m_oneinchar = 0;
    m_version = 1;      //0 is first version TCD, 1 is second version TCD;
}

QString ImageBase::GetPictureNumber(const QImage &image)
{
    targetImage = image;
    return getPicNumber();
}

QString ImageBase::GetPictureNumber(const QString &fileName)
{
    targetImage = QImage(fileName);
    return getPicNumber();
}

void ImageBase::TestNumber(const QImage &image)
{
    targetImage = image;
    testNumber();
}

void ImageBase::TestNumber(const QString &fileName)
{
    targetImage = QImage(fileName);
    testNumber();
}

int ImageBase::getGrayNumberColor(QColor color)
{
    return (color.red() * 19595 + color.green() * 38469 + color.blue() * 7472) >> 16;
}

void ImageBase::grayByPixels()
{
    for (int i = 0; i < targetImage.height(); i++)
    {
        for (int j = 0; j < targetImage.width(); j++)
        {
            int tmpValue = getGrayNumberColor(targetImage.pixel(j, i));
            targetImage.setPixel(j, i, QColor(tmpValue, tmpValue, tmpValue).rgba());
        }
    }

}

QString ImageBase::getSingleBmpCode(const QImage &image, int grayValue)
{
    m_oneinchar = 0;
    QString code = "";
    for (int posy = 0; posy < image.height(); posy++)
    {
        for (int posx = 0; posx < image.width(); posx++)
        {
            QColor piexl = image.pixel(posx, posy);
            if (piexl.red() < grayValue)    // Color.Black
            {
                m_oneinchar++;
                code = code + "1";
            }
            else
            {
                code = code + "0";
            }
        }
    }

    //qDebug() << "m_one is:" << m_oneinchar <<endl;
    return code;
}

QList<QImage> ImageBase::getPicValidByValue(int grayValue)
{
    QList<QImage> picList;
    QRect cloneRect;
    int posx1 = targetImage.width();
    int posy1 = targetImage.height();
    int posx2 = 0, posy2 = 0;
    bool cut = false;
    int last = -1; // lastx = 0;
    for (int j = 0; j < targetImage.width(); j++)      //找有效区
    {
        cut = false;
        for (int i = 0; i < targetImage.height(); i++)
        {
            int pixelValue = QColor(targetImage.pixel(j, i)).red();
            if (pixelValue < grayValue)     //根据灰度值
            {
                if (posx1 > j)
                    posx1 = j;
                if (posy1 > i)
                    posy1 = i;

                if (posx2 < j)
                    posx2 = j;
                if (posy2 < i)
                    posy2 = i;
                cut = true;
            }
        };

        if (cut)
            continue;
        if (last + 1 == j)
        {
            last++;
            continue;
        }

        cloneRect = QRect(posx1, posy1, posx2 - posx1 + 1, posy2 - posy1 + 1);
       // lastx = j;
        last = j;
        posx1 = targetImage.width();
        posy1 = targetImage.height();
        posx2 = 0;
        posy2 = 0;
        picList << targetImage.copy(cloneRect);//复制小块图
    };

    return picList;
}

QString ImageBase::getPicNumber()
{
    grayByPixels(); //灰度处理
    QList<QImage> pics = getPicValidByValue(128); //得到有效值
       //    qDebug() << pics.length() << endl;
    QString ret;
    int j =0;
    for (int i = 0; i < pics.length(); ++i)
    {
        QString code = getSingleBmpCode(pics[i], 128);   //得到代码串

        //QString currstr = "strange";
        //currstr += QString::number(i);
        //currstr += ".png";
        //pics[i].save(currstr);

        //  qDebug() << code << endl;

         for(j =0 ; j < numberDictionary.count(); j++)
         {
             int nlevel = 0;
             QString dicstr = numberDictionary.keys().at(j);
             nlevel = CompareLikeLevel(code,dicstr);
             if(nlevel == 0 ) //|| nlevel == 100)  //equal string
             {
                 //qDebug() << "equalstring:" <<code <<endl;
                 ret.append(numberDictionary.value(dicstr));
                 break;
             }
         }
         if( j  == numberDictionary.count())  //fill "?" to replace the acutal cannot find number
         {
             ret.append("?");
         }


//        if (numberDictionary.find(code) != numberDictionary.end())
//        {
//                  qDebug() << "value: " << numberDictionary.value(code) << endl;
//            ret.append(numberDictionary.value(code));
//        }


    }

    m_resultList << ret;

    return ret;
}

int ImageBase::CompareLikeLevel(QString strA, QString strB)
{
    int ret = 1;
    int equalstr =  -1;
    int len_a = 0, len_b = 0;

    int oneinA = 0, oneinB = 0;
    len_a = strA.count();
    len_b = strB.count();

    oneinA = strA.count('1');
    oneinB = strB.count('1');


    equalstr = QString::compare(strA,strB);
    if(!equalstr) // equal string
    {
        return 0;
    }

    if(qFabs(oneinA - oneinB ) <= 2   )     //number of '1' is same
    {


       // if(qFabs(len_a - len_b) <= 3)   //same length string
       // {
            QString strlfhalf = strA.left(len_a / 2);
            QString strrthalf = strA.right(len_a / 2);

            if(strB.contains(strlfhalf) || strB.contains(strrthalf) )  //at least half string appears in it!
            {
                ret = 0;
            }
            else
            {
                ret = 100;
            }

            if(ret == 100)
            {
                // -------- spph old -verion 0 --
                //                if(qFabs(oneinA - 106) <= 3)   //only process 5
                //                {
                //                     int more_ylen = 0;
                //                     more_ylen = qFabs(len_a - len_b);
                //                     if((more_ylen % 14) == 0)  //it is really more y lenth. same number
                //                     {
                //                        ret  = 0;
                //                     }
                //                }
                // ------ spph end --------

                // if(qFabs(oneinA - 106) <= 3)   //only process 5
                // {
                      int more_ylen = 0;
                      more_ylen = qFabs(len_a - len_b);
                      if((more_ylen % 14) == 0)  //it is really more y lenth. same number
                      {

                         if(m_version == 0)
                         {
                            ret  = 0;
                         }
                         if(m_version == 1)   //second old version TCD, 0,6 is equal
                         {
                             bool Azero = strA.contains("1111111111001111001111");  // "0"
                             bool Bzero = strB.contains("1111111111001111001111");

                             bool ATwo = strA.contains("0011111000011111111100"); //"2"
                             bool BTwo = strB.contains("0011111000011111111100"); //"2"

                             bool AThree = strA.contains("1111100000001111111");  //"3"
                             bool BThree = strB.contains("1111100000001111111");  //"3"

                             bool Asix = strA.contains("00011111111100111110000000");  //  "6"
                             bool Bsix = strB.contains("00011111111100111110000000");  //  "6"

                             bool Aeight = strA.contains("1111011111011110001111111");  // "8"
                             bool Beight = strB.contains("1111011111011110001111111");  // "8"

                             bool ASeven = strA.contains("11111111111111111111111111111111111100000001"); //"7"
                             bool BSeven = strB.contains("11111111111111111111111111111111111100000001"); //"7"

                             bool Anine = strA.contains("11111111000011111100000");  //  "9"
                             bool Bnine = strB.contains("11111111000011111100000");  //  "9"

                             if((Azero && Bzero) || (ATwo && BTwo)|| (AThree && BThree) ||(Asix && Bsix)||(ASeven && BSeven) || (Aeight && Beight)|| (Anine && Bnine) )
                             {

                                  ret = 0;

                             }

                         }
                      }
               //  }     //process 5


            }


       // }

    }
    else
    {
        ret = -1;
    }

    return ret;

}

void ImageBase::testNumber()
{
    grayByPixels(); //灰度处理
    QList<QImage> pics = getPicValidByValue(128); //得到有效值
    for (int i = 0; i < pics.length(); ++i)
    {
        QString code = getSingleBmpCode(pics[i], 128);   //得到代码串
       // qDebug() << i << endl;
       // qDebug() << code << endl;
    }


}
QString ImageBase::GetBloodString(const QImage &inputimage)
{
    QString strcode ;
    QString retstr;



    strcode = getSingleBmpCode(inputimage,128);
    //qDebug() << "number is:" << m_oneinchar << endl;
    //    QImage bakimage;

    //    bakimage = targetImage;
    //    targetImage = inputimage;

    //    QList<QImage> pics = getPicValidByValue(128);

    //    targetImage = bakimage;

    int j =0;
    for(j =0 ; j < bloodDictionary.count(); j++)
    {

        int savenumber = bloodDictionary.keys().at(j);
        if(qFabs(savenumber - m_oneinchar) <= 3)    //simliar string ,need further check
        {

             if((qFabs(savenumber - 384 ) <= 2) || (qFabs(savenumber - 342 ) <= 2) ) //is r/l-aca or r/l-pca
             {
                 QString verticalstr;
                 verticalstr = getVerticalSingleBmpCode(inputimage, 128);
                 QString pstr = "0000111111111111111000000001111111111111110000000011111111111111100000000111000111000000000000001110001110000000000000011100011100000000000000111000111000000000000001110001110000000000000001111111000000000000000011111110000000000000000001110000000000000";

                 if(verticalstr.contains(pstr))    //pca
                 {
                     retstr = bloodDictionary.value(savenumber);
                 }
                 else
                 {
                     if((qFabs(savenumber - 384 ) <= 2))
                     {
                       retstr = "R-ACA";
                     }
                     if((qFabs(savenumber - 342 ) <= 2))
                     {
                        retstr = "L-ACA";
                     }
                     break;
                 }

             }
             else
             {
               retstr = bloodDictionary.value(savenumber);
             }

        }

    }

    return retstr;
}

bool ImageBase::GetAndSplitInputImage(const QImage &inputimage)
{
    //m_imageblock

    QList<int> blockorder;
    bool totalimage_have_rightedge = false;

    int i,j;
    int line = 0;
    m_inputImage = inputimage;
    int width  = m_inputImage.width();
    int height = m_inputImage.height();

    blockorder.append(0);

    m_resultList.clear();

    if ((width ==0 ) && height == 0)
    {
        qDebug() <<"Invalid input Image!" <<endl;
        return false;
    }

    int lastval = 0;

    for(i = 0; i < width; i++)
    {
        line = 0;
        for(j = 0; j < height; j++)
        {
          QColor pixcolor = m_inputImage.pixel(i,j);

          if((pixcolor.red() < 150 ) && (pixcolor.green() < 150))  // darkline
          {
              line++;
          }
          else
          {
              break;
          }

        }
        if(line > (height/2))
        {
            if((i - lastval) > 40)    //i is real next gap
            {
                blockorder.append(i+1);
//                if((width - i) <= 2) //the image have right edge
//                {
//                    totalimage_have_rightedge = true;
//                }
                lastval = i;
            }


        }

    }

    if((width-lastval) > 40)             //!totalimage_have_rightedge)
    {
        blockorder.append(width - 1);
    }

    QRect blockrect;
    QImage block;

    if(blockorder.count() == 1)
        return false;

    int avaragelen = width /(blockorder.count() -1) ;

    for(i = 0; i < (blockorder.count() -1); i++)
    {
        QString str =  "block";    //"./templates/block";
        int leftedge = blockorder.at(i);

        blockrect = QRect(leftedge+2,2, avaragelen - 6, height - 4 );
        m_imageblock.append(m_inputImage.copy(blockrect));

        block = m_imageblock.at(i);
        str += QString::number(i,10);
        str += ".png";
        block.save(str);
        m_fileList << str;
        // qDebug<< str + QString::number(i,10) <<endl;
    }

    for (int i = 0; i < m_fileList.count(); ++i)
    {
       GetPictureNumber(m_fileList[i]) ;
      // QFile::remove(m_fileList[i]);
    }
    return true;

}


QString ImageBase::getVerticalSingleBmpCode(const QImage &image, int grayValue)
{
        QString code = "";

        for (int posx = 0; posx < image.width(); posx++)
        {
            for (int posy = 0; posy < image.height(); posy++)
            {
                QColor piexl = image.pixel(posx, posy);
                if (piexl.red() < grayValue)    // Color.Black
                {
                    // m_oneinchar++;
                    code = code + "1";
                }
                else
                {
                    //m_zeroinchar++;
                    code = code + "0";
                }
            }
        }

    return code;
}
