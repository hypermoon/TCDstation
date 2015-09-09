#ifndef IMAGEBASE_H
#define IMAGEBASE_H

#include <QObject>
#include <QImage>
#include <QColor>
#include <QMap>
class ImageBase : public QObject
{
    Q_OBJECT
public:
    explicit ImageBase(QObject *parent = 0);

    //外部调用，输入图片名字，会将图片划分为数字小块图。
    bool GetAndSplitInputImage(const QImage &inputimage);

    //外部调用， 取得分析返回结果
    QStringList GetResult() {return m_resultList;};

    QString GetBloodString(const QImage &inputimage);
public:
    //外部调用，得到一个图片的数字串
    virtual QString GetPictureNumber(const QImage &image);

    //外部调用，得到一个图片的数字串(重载）
    QString GetPictureNumber(const QString &fileName);
protected:
    //外部调用，输出在一幅图里面找到的数字，测试或者找到数字比对串时用
    void TestNumber(const QImage &image);

    //外部调用，输出在一幅图里面找到的数字，测试或者找到数字比对串时用（重载）
    void TestNumber(const QString &fileName);

private:
    //得到图片中某一点的灰度数值
    int getGrayNumberColor(QColor color);

    //进行灰度处理
    void grayByPixels();

    //得到一个图片的01序列
    QString getSingleBmpCode(const QImage& image, int grayValue);

    //得到一个图片的01序列  (vertical direction)
    QString getVerticalSingleBmpCode(const QImage &image, int grayValue);

    //从一个图片里得到几个分开的数字小图片
    QList<QImage> getPicValidByValue(int grayValue);

    //得到一个图片的数字串
    QString getPicNumber();
    //内部小图片块
    QList<QImage>  m_imageblock;

    //输出在一幅图里面找到的数字，测试或者找到数字比对串时用
    void testNumber();

    //比较两个字符串相似程度
    int CompareLikeLevel(QString, QString);

signals:

public slots:

public:
    QMap<QString, char> numberDictionary;

    QMap<int ,QString> bloodDictionary;
private:


    QStringList m_fileList;       //block image file name list

    QImage targetImage;

    QImage m_inputImage;

    QStringList m_resultList;     //result string list

    int m_oneinchar;

    bool m_version;

};

#endif // IMAGEBASE_H
