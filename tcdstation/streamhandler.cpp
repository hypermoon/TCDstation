#include "streamhandler.h"

StreamHandler::StreamHandler(QObject *parent) :
    QObject(parent),m_pCapture(NULL)
{
    m_pCapture = cvCaptureFromCAM(-1);
    if (m_pCapture != NULL)
    {
        cvQueryFrame(m_pCapture);
        int width = (int)cvGetCaptureProperty(m_pCapture, CV_CAP_PROP_FRAME_WIDTH);
        int height = (int)cvGetCaptureProperty(m_pCapture, CV_CAP_PROP_FRAME_HEIGHT);
        m_Label.setFixedSize(width, height);
    }
}

StreamHandler::~StreamHandler()
{
    cvReleaseCapture(&m_pCapture);
}

bool StreamHandler::Screenshot(const QString path)
{
    QRect rect; // Default Rect;
    return m_Label.grab(rect).save(path);
}

void StreamHandler::getCurrentFrame()
{
    IplImage *image = cvQueryFrame(m_pCapture);

    cvConvertImage(image, image, CV_BGR2RGB);
    m_Image = QImage((uchar*)image->imageData, image->width, image->height, image->widthStep, QImage::Format_RGB888);
    m_Label.setPixmap(QPixmap::fromImage(m_Image));

    emit(updateFrame(m_Image));
}
