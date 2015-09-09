#ifndef STREAMHANDLER_H
#define STREAMHANDLER_H

#include <QObject>
#include "cv.h"
#include "highgui.h"
#include <QImage>
#include <QLabel>

class StreamHandler : public QObject
{
    Q_OBJECT
public:
    explicit StreamHandler(QObject *parent = 0);
    ~StreamHandler();
    bool Screenshot(const QString path);
private:
    void getCurrentFrame();
signals:
    void updateFrame(const QImage );

public slots:

private:
    CvCapture *m_pCapture;
    QImage     m_Image;
    QLabel     m_Label;

};

#endif // STREAMHANDLER_H
