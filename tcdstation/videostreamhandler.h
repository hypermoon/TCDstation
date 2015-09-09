#ifndef VIDEOSTREAMHANDLER_H
#define VIDEOSTREAMHANDLER_H
#include <QTimer>
#include <QImage>
#include "opencv/cv.h"
#include "opencv/highgui.h"

class VideoStreamHandler
{
public:
    VideoStreamHandler();
    ~VideoStreamHandler();
    const QImage GetImage();
    const int GetWidth() const;
    const int GetHeight() const;

private:
    QTimer     m_timer;
    CvCapture *m_pCapture;
    int       m_Width;
    int       m_Height;
};

#endif // VIDEOSTREAMHANDLER_H
