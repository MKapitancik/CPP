#pragma once
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "configuration.h"
#include <iostream>

using namespace std;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** @brief Treida pre predspracovanie a segmentaciu obrazu pomocou Cannyho / druhej derivacii
	metoda: doWork(Mat im) vrati binnarny obraz z ktoreho su ziskavane kontury
*/
class imadjust
{
	cv::Mat grayIm;
public:
	///C´tors
	imadjust();		
	///Methods	
	cv::Mat im2gray(const cv::Mat &im);
	double medianMat(cv::Mat Im);	//Get median of grayscale image
	cv::Mat imThresh(cv::Mat &im, bool UseCannyThreshold = true);	//get Edge of image with specific threshold of gradient, if second parameter is false/zero then second derivation is used for e. image
	cv::Mat RemoveStandAlonePixels(cv::Mat &im);		//Remove standalone pixels	
	cv::Mat doWork(cv::Mat &im);		//Worker method
	cv::Mat GrayIm() { return grayIm; }
	///D´tor
	~imadjust();
};

