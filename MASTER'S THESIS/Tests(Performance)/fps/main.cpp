#include "opencv2/opencv.hpp"
#include <time.h>
#include <QElapsedTimer>
#include <linux/videodev2.h>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    QElapsedTimer timer;
    // Start default camera
    VideoCapture video(0);
    if(!video.isOpened())  // check if we succeeded
        return -1;

    // With webcam get(CV_CAP_PROP_FPS) does not work.
    // Let's see for ourselves.
    video.set(CV_CAP_PROP_FPS, 25);
    video.set(CV_CAP_PROP_FRAME_WIDTH, 1800);
    video.set(CV_CAP_PROP_FRAME_HEIGHT, 1600);

    double fps = video.get(CV_CAP_PROP_FPS);
    // If you do not care about backward compatibility
    // You can use the following instead for OpenCV 3
    // double fps = video.get(CAP_PROP_FPS);
    cout << "Frames per second using video.get(CV_CAP_PROP_FPS) : " << fps << endl;
    cout << "Resoluction : " << video.get(CV_CAP_PROP_FRAME_WIDTH) << " x " << video.get(CV_CAP_PROP_FRAME_HEIGHT) << endl;

    // Number of frames to capture
    int num_frames = 50;

    timer.start();
    // Start and end times
    time_t start, end;

    // Variable for storing video frames
    Mat frame;

    cout << "Capturing " << num_frames << " frames" << endl ;

    // Start time
    time(&start);

    // Grab a few frames
    for(int i = 0; i < num_frames; i++)
    {
        video >> frame;
    }

    // End Time
    time(&end);
    double sec = timer.elapsed() / 1000;

    // Time elapsed
    double seconds = difftime (end, start);
    cout << "Time taken : " << seconds << " seconds" << endl;

    // Calculate frames per second
    fps  = num_frames / seconds;
    cout << "Estimated frames per second : " << fps << endl;
    cout << "Qtimer estimated: " << num_frames / sec << endl;

    // Release video
    video.release();
    return 0;
}
