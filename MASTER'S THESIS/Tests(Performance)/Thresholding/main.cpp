#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QDebug>
#include <QElapsedTimer>
#include <string>

using namespace std;
using namespace cv;

string type2str(int type);

int main()
{
    QElapsedTimer timer;
    Mat img1;
    Mat dest;
    qint64 time1;
    time1 = 0;
    int plot, metoda;
    double prah = 0;
    string ty;

    img1 = imread("/home/pi/Pictures/Testy/blurr/reptile_look_chameleon_73102_800x600.jpg");
    cvtColor( img1, img1, CV_BGR2GRAY );

    cout << "zadaj jedna pre orig, 0 pre blurred :";
    cin >> plot;

    while(true)
    {
        cout << "zadaj prah 0-255 :";
        cin >> prah;
        if(0 == prah)
            break;
        cout << "zadaj typ 0-4 :";
        cin >> metoda;

        if(!img1.data)
        {
            cout << "Nejde otvorit pozadovany obrazok" << endl;
            return 1;
        }

        timer.start();
       // threshold(img1,dest,prah,255,metoda | CV_THRESH_OTSU);
        adaptiveThreshold(img1,dest,255,CV_ADAPTIVE_THRESH_MEAN_C,CV_THRESH_BINARY,15,0);
        time1 = timer.elapsed();
        cout << "time(ms)" << time1 << endl;

        if(plot)
        {
            namedWindow("orig",WINDOW_AUTOSIZE);
            imshow("orig", img1);
        }
        else
        {
            namedWindow("blured",WINDOW_AUTOSIZE);
            imshow("blured", dest);
        }
        waitKey();
    }

    ty = type2str(dest.type());
    cout << "Matrix :" << ty.c_str() << " " << dest.cols << "x" << dest.rows << endl;
    return 0;
}

string type2str(int type) {
  string r;

  uchar depth = type & CV_MAT_DEPTH_MASK;
  uchar chans = 1 + (type >> CV_CN_SHIFT);

  switch ( depth ) {
    case CV_8U:  r = "8U"; break;
    case CV_8S:  r = "8S"; break;
    case CV_16U: r = "16U"; break;
    case CV_16S: r = "16S"; break;
    case CV_32S: r = "32S"; break;
    case CV_32F: r = "32F"; break;
    case CV_64F: r = "64F"; break;
    default:     r = "User"; break;
  }

  r += "C";
  r += (chans+'0');

  return r;
}

