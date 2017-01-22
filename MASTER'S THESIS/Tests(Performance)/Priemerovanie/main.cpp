#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QDebug>
#include <QElapsedTimer>
#include <string>

using namespace std;
using namespace cv;


// Canny(dest,dest,80,100);
// blur(img,dest,Size(5, 5));
// GaussianBlur(img,img,Size(7,7),0);
// medianBlur(img,dest,35);
// bilateralFilter(img,dest,25,9,3);

#define MAXCNT  1

string type2str(int type);

int main()
{
    QElapsedTimer timer;
    Mat img1, img2, img3;
    Mat dest;
    qint64 time1,time2,time3;
    time1 = time2 = time3 = 0;
    string ty;
    Size siz(5,5);
    int plot;

    cout << "zadaj jedna pre orig, 0 pre blurred :";
    cin >> plot;

    for (int count = 0; count <  MAXCNT; count++)
    {
        img1 = imread("/home/pi/Pictures/Testy/blurr/reptile_look_chameleon_73102_800x600.jpg");
        img2 = imread("/home/pi/Pictures/Testy/blurr/reptile_look_chameleon_73102_1280x720.jpg");
        img3 = imread("/home/pi/Pictures/Testy/blurr/reptile_look_chameleon_73102_1280x720N.jpg");

        if(!img1.data && !img2.data && !img3.data)
        {
            cout << "Nejde otvorit pozadovany obrazok" << endl;
            return 1;
        }

        ty = type2str(img1.type());
        cout <<" count : " << count << " <> Matrix :" << ty.c_str() << " " << img1.cols << "x" << img2.rows << endl;

        timer.start();
        blur(img1,dest,siz);
        time1 += timer.elapsed();

        timer.start();
        blur(img2,dest,siz);
        time2 += timer.elapsed();

        timer.start();
        blur(img3,dest,siz);
        time3 += timer.elapsed();
    }
    //cvtColor(img1,img1,CV_BGR2GRAY);
    cout << "800x600 time(ms)" << time1/MAXCNT << endl;
    cout << "1280x720 time(ms)" << time2/MAXCNT << endl;
    cout << "1920x1080 time(ms)" << time3/MAXCNT << endl;

    if(plot)
    {
        namedWindow("orig",WINDOW_AUTOSIZE);
        imshow("orig", img3);
    }
    else
    {
        namedWindow("blured",WINDOW_AUTOSIZE);
        imshow("blured", dest);
    }

    ty = type2str(dest.type());
    cout << "Matrix :" << ty.c_str() << " " << dest.cols << "x" << dest.rows << endl;
    waitKey(0);
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

