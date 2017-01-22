#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QDebug>
#include <QElapsedTimer>
#include <string>

using namespace std;
using namespace cv;

#define MAXCNT  10

string type2str(int type);

int main()
{
    QElapsedTimer timer;
    Mat img1, img2, img3;
    Mat tmp1, tmp2, tmp3;
    Mat dest;
    Mat element = getStructuringElement(CV_SHAPE_RECT,Size(5,5));
    Mat dst;
    qint64 time1,time2,time3;
    time1 = time2 = time3 = 0;
    string ty;
    int siz = 5;
    int plot;

    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;

    cout << "zadaj jedna pre orig, 0 pre blurred :";
    cin >> plot;

    for (int count = 0; count <  MAXCNT; count++)
    {
        tmp1 = imread("/home/pi/Pictures/Testy/blurr/reptile_look_chameleon_73102_800x600.jpg",0);
        tmp2 = imread("/home/pi/Pictures/Testy/blurr/reptile_look_chameleon_73102_1280x720.jpg",0);
        tmp3 = imread("/home/pi/Pictures/Testy/Hrany/Amarker.jpg",0);

        if(!tmp1.data && !tmp2.data && !tmp3.data)
        {
            cout << "Nejde otvorit pozadovany obrazok" << endl;
            return 1;
        }

        ty = type2str(img1.type());
        cout <<" count : " << count << " <> Matrix :" << ty.c_str() << " " << img1.cols << "x" << img2.rows << endl;

        Mat grad_x, grad_y;
        Mat abs_grad_x, abs_grad_y;

        timer.start();
        /// Gradient X
        //Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
        Sobel( tmp1, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
        convertScaleAbs( grad_x, abs_grad_x );


        /// Gradient Y
        //Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
        Sobel( tmp1, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
        convertScaleAbs( grad_y, abs_grad_y );

        /// Total Gradient (approximate)
        addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dest );
        time1 += timer.elapsed();


        timer.start();
        /// Gradient X
        //Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
        Sobel( tmp2, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
        convertScaleAbs( grad_x, abs_grad_x );

        /// Gradient Y
        //Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
        Sobel( tmp2, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
        convertScaleAbs( grad_y, abs_grad_y );
        /// Total Gradient (approximate)
        addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dest );
        time2 += timer.elapsed();

        timer.start();
        /// Gradient X
        //Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
        Sobel( tmp3, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
        convertScaleAbs( grad_x, abs_grad_x );

        /// Gradient Y
        //Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
        Sobel( tmp3, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
        convertScaleAbs( grad_y, abs_grad_y );
        addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dest );
        time3 += timer.elapsed();
        /// Total Gradient (approximate)
        ///
        dest = dest > 128;
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
