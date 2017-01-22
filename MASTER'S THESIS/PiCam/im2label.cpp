#include "im2label.h"

Im2Label::Im2Label(QObject *parent)
    : QThread(parent)
{
    capture = new VideoCapture(0);
    while(!capture->isOpened());
    capture->set(CV_CAP_PROP_FPS,30);
    frameRate = (int) capture->get(CV_CAP_PROP_FPS);
    capture->set(CV_CAP_PROP_FRAME_WIDTH, 800);
    capture->set(CV_CAP_PROP_FRAME_HEIGHT, 600);
    stop = false;
}

void Im2Label::run(){
    int delay = (1000/frameRate);
    while(!stop)
    {
        if (!capture->read(frame)){
            stop = true;
        }
        if (frame.channels() == 3){
            cvtColor(frame,RGBframe,CV_BGR2RGB);
            img = QImage((const unsigned char*)(RGBframe.data),RGBframe.cols,RGBframe.rows,QImage::Format_RGB888);
        }
        else
        {
            static QVector<QRgb>  sColorTable;

            // only create our color table once
            if ( sColorTable.isEmpty() )
            {
               for ( int i = 0; i < 256; ++i )
                  sColorTable.push_back( qRgb( i, i, i ) );
            }
            img =  QImage((const unsigned char*)(frame.data), frame.cols,frame.rows,QImage::Format_Indexed8);
            img.setColorTable(sColorTable);
        }
        emit processedImage(img);
        this->msleep(delay);
    }
}

void Im2Label::play(){
    start(LowPriority);
}

Im2Label::~Im2Label(){
    mutex.lock();
    stop = true;
    capture->release();
    condition.wakeOne();
    delete capture;
    mutex.unlock();
    wait();
}

void Im2Label::msleep(int ms){
    struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);
}

void Im2Label::setCamParam(int CV_property, double value){
    capture->set(CV_property, value);
}



