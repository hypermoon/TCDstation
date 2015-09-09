#include "videostreamhandler.h"

VideoStreamHandler::VideoStreamHandler()
    : m_pCapture(NULL)
{
    m_pCapture = cvCaptureFromCAM(-1);
    if (m_pCapture != NULL)
    {
        m_Width = (int)cvGetCaptureProperty(m_pCapture, CV_CAP_PROP_FRAME_WIDTH);
        m_Height = (int)cvGetCaptureProperty(m_pCapture, CV_CAP_PROP_FRAME_HEIGHT);
    }
}


VideoStreamHandler::~VideoStreamHandler()
{
    if (m_pCapture != NULL)
    {
        cvReleaseCapture(&m_pCapture);
        m_pCapture = NULL;
    }
}

const QImage VideoStreamHandler::GetImage()
{
    if (m_pCapture == NULL)
        return QImage();

    IplImage *pImage = cvQueryFrame(m_pCapture);
    if (pImage == NULL)
        return QImage();

    cvConvertImage(pImage, pImage, CV_CVTIMG_SWAP_RB);

    QImage image = QImage((uchar*)pImage->imageData, pImage->width, pImage->height, pImage->widthStep, QImage::Format_RGB888);

    return image;
}

const int VideoStreamHandler::GetWidth() const
{
    return m_Width;
}

const int VideoStreamHandler::GetHeight() const
{
    return m_Height;
}
