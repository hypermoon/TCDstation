#ifndef TCDIMAGE_H
#define TCDIMAGE_H
#include "imagebase.h"
class TcdImage : public ImageBase
{
public:
    TcdImage();

    //外部调用接口,传入血管图片,返回血管字符串
    QString GetBloodType();

    //外部调用接口,传入总体数字图片,返回分析的全部数字list
    QStringList GetnDataValues ();


    //外部调用接口,载入总体图片
    bool LoadWholeImage (const QImage &image);

private:

    QImage m_dataValueImage;
    QImage m_bloodImage;

};

#endif // MYIMAGE_H
