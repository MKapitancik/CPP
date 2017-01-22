#ifndef IM2LABEL_H
#define IM2LABEL_H

#include <QMutex>
#include <QThread>
#include <QImage>
#include <QWaitCondition>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
class Im2Label : public QThread
{Q_OBJECT
private:
    bool stop;
    QMutex mutex;
    QWaitCondition condition;
    Mat frame;
    int frameRate;
    VideoCapture *capture;
    Mat RGBframe;
    QImage img;
signals:
    void processedImage(const QImage &image);
protected:
    void run();
    void msleep(int ms);
public:
    Im2Label(QObject *parent = 0);
    void play();
    void setCamParam(int CV_property, double value);
    virtual ~Im2Label();
};

#endif // IM2LABEL_H
