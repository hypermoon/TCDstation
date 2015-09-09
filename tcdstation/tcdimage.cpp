#include "tcdimage.h"

TcdImage::TcdImage()
{
//    numberDictionary.insert("1111111111111111", '.');
//    numberDictionary.insert("111111111111111111111",'-');
//    numberDictionary.insert("000111111000001111111100011111111110011110011111111100001111111100001111111100001111111100001111111100001111111100001111011110011111011111111110001111111110000111111000", '0');
//    numberDictionary.insert("000111000001111000111111000111111000111111000000111000000111000000111000000111000000111000000111000111111111111111111111111111", '1');
//    numberDictionary.insert("0111111100011111111110111111111101100001111000000001110000000011100000001111000000111100000011110000001111000001111000000111111111111111111111111111111111", '2');
//    numberDictionary.insert("001111111000011111111110011111111110010000001110000000011110000011111100000011111000000011111110000000001111000000001111110000011111111111111110111111111110001111111000", '3');
//    numberDictionary.insert("000000111100000001111100000001111100000011111100000111011100001110011100011100011100111000011100111111111111111111111111111111111111000000011100000000011100000000011100",'4');
//    numberDictionary.insert("1111111111011111111110111111111101111000000011110000000111111110001111111111011111111111000000011110000000111110000001111111111111101111111110001111111000", '5');
//    numberDictionary.insert("000001111110000111111110001111111110011111000000011110000000011111111100111111111110111111111111111100001111011100001111011110001111011111111111001111111110000011111000", '6');
//    numberDictionary.insert("1111111111111111111111111111111110000000111100000011110000001111100000011110000001111000000011110000001111000000111110000001111000000111100000011111000000", '7');
//    numberDictionary.insert("000111111000011111111110011111111111011100001111011100001111011111111110001111111100001111111110011100011111111100001111111100001111111111111111011111111110000111111000", '8');
//    numberDictionary.insert("000111111000001111111100011111111110111100011111111100001111111100001111111111111111011111111111001111111111000000001110000000111110011111111100011111111000011111100000", '9');

    numberDictionary.insert("1111111111111111", '.');
    numberDictionary.insert("111111111111111111111",'-');
    numberDictionary.insert("000011110000001111111100011111111110011110011110111100001111111100001111111100001111111100001111111100001111111100001111011110011110011111111110001111111100000011110000", '0');
    numberDictionary.insert("00001110000001111000111111100011111110001111111000000111100000011110000001111000000111100000011110000001111000111111111111111111111111111111", '1');
    numberDictionary.insert("0011111000011111111100111111111101000001111000000011110000000111100000001110000000111000000011100000001110000001111000000111111111111111111111111111111111", '2');
    numberDictionary.insert("001111111000111111111110111111111111100000001111000000001110000011111100000011111000000011111110000000001111000000001111100000011111111111111110111111111100001111110000", '3');
    numberDictionary.insert("000000111100000001111100000011111100000111111100000110111100001100111100011000111100111000111100111111111111111111111111111111111111000000111100000000111100000000111100",'4');
    numberDictionary.insert("0111111111101111111111011111111110111100000001111000000011111110000111111111001111111111000000011110000000111110000001111111111111101111111110000111110000", '5');
    numberDictionary.insert("000001111110000111111110001111111110011111000000011100000000111101111000111111111110111111111111111100001111111100001111011100001111011111111110001111111110000011111000", '6');
    numberDictionary.insert("111111111111111111111111111111111111000000011111000000011110000000111100000000111100000001111000000011111000000011110000000111110000000111100000001111000000011111000000", '7');
    numberDictionary.insert("000111111000011111111110111111111111111100001111111100001111011111011110001111111000001111111110011100011111111100001111111100001111111111111110011111111110000111111000", '8');
    numberDictionary.insert("000011110000001111111100011111111110111100001110111100001111111100001111111111111111011111111111000111101111000000011110000000111110011111111100011111111000011111100000", '9');



    //bloodDictionary

    /*QString str[12];

    str[0] = "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
    str[1] = "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
    str[2] = "000000001111111111000000000000111100000111110000001111110000000001111000000000000000000000000000001111111111100000000000111110000111110000011111111100000001111100000000000000000";
                           000000000001111111111110000000000111110000111110000111111111100000001111100000000000000000000000000001110000001110000000000111110000111110001111000011110000011111110000000000000
                           000000000000001110000001110000000000111110001111110001110000001000000011101110000000000000000000000000001110000001110000000000111010001101110011100000000000000011001110000000000
                           000000000000000001111111111100000000000111011001001110011100000000000000111000111000000000000000000000000001111111111100000000000111011001001110011100000000000000111000111000000
                           000000000000000000001111111100000011111100111011011001110011100000000000000111000111000000000000000000000000001110001110000011111100111011011001110011100000000000001111111111100
                           000000000000000000000001110001111000011111100111001011001110001110000001100001111111111100000000000000000000000001110000111100000000000111001111001110001111000011110001111111111
                           110000000000000000000000001110000011110000000000111001111001110000111111111110011100000001110000000000000000000000001110000001110000000000111001110001110000011111111100011100000
                           001110000000000000000000000001110000001111000000000111001110001110000001111110000111100000000111000000000000000000000000000000000000000000000000000000000000000000000000000000000
                           000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
                           000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",R-MCA");
                           */
//    bloodDictionary.insert(477,"R-MCA");
//    bloodDictionary.insert(437,"R-ACA");
//    bloodDictionary.insert(431,"R-PCA");
//    bloodDictionary.insert(425,"L-MCA");
//    bloodDictionary.insert(385,"L-ACA");
//    bloodDictionary.insert(378,"L-PCA");
//    bloodDictionary.insert(325,"R-VA");
//    bloodDictionary.insert(273,"L-VA");
//    bloodDictionary.insert(240,"BA");

    bloodDictionary.insert(445,"R-MCA");
    bloodDictionary.insert(384,"R-ACA");
    bloodDictionary.insert(386,"R-PCA");
    bloodDictionary.insert(402,"L-MCA");
    bloodDictionary.insert(342,"L-ACA");
    bloodDictionary.insert(344,"L-PCA");
    bloodDictionary.insert(288,"R-VA");
    bloodDictionary.insert(248,"L-VA");
    bloodDictionary.insert(215,"BA");

    // numberDictionary.insert("111111111100011111111111001111111111100111000000111011100000011101110000001110111111111110011111111110001111111100000111001111000011100011110001110000111100111000001110011100000011101110000001111",'R');
    // numberDictionary.insert("111111111111111111",'-');
    // numberDictionary.insert("111100000111111111000001111111111000011111111110000111111111100011111111111000111111111010001011111110110010111111101101101111111011011001111110010110011111100111100111111001110001111110011100011111000111000111",'M');
    // numberDictionary.insert("000011111100000011111111000111111111110011110000111101110000001001110000000000111000000000011100000000001110000000000111000000000001110000001100111100001111001111111111000011111111100000111111000",'C');
    // numberDictionary.insert("000001111000000000001111100000000001111100000000011111100000000011101110000000011001110000000111000111000000111000111000000110000111000001111111111100001111111111100011111111111100011100000001110011100000001110111000000000111",'A');

}


QString TcdImage::GetBloodType()
{
    if(!m_bloodImage.isNull())
    {
       return ImageBase::GetBloodString(m_bloodImage);
    }
    return NULL;
}


 QStringList TcdImage::GetnDataValues ()
 {
     if(!m_dataValueImage.isNull())
     {
        ImageBase::GetAndSplitInputImage(m_dataValueImage);
     }

     return ImageBase::GetResult();

 }

 bool TcdImage::LoadWholeImage (const QImage &image)
 {
     QImage inputimage;
     inputimage = image;

     inputimage.save("wholeimage.png");

     inputimage.save("wholeimageinput.png");

     QRect rect(3,30,590,45);
     QRect rectblood(93,3,90,23);
     m_dataValueImage = inputimage.copy(rect);

     m_dataValueImage.save("wholedata.png");

     //m_dataValueImage.save("newtt.png");


     m_bloodImage = inputimage.copy(rectblood);
     m_bloodImage.save("ttnew.png");
 }
