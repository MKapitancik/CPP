#include "imadjust.h"
using namespace cv;
/**	@brief Default C´tor
*/
imadjust::imadjust()
{
}
/**	@brief D´tor
*/
imadjust::~imadjust()
{
}
/**	@brief Method for image to gray transformation	
*	@param im: BGR image
*	@out: gray image
*/
Mat imadjust::im2gray(const Mat & im)
{	
	if (im.channels() == 3)
	{
		cvtColor(im, grayIm, CV_BGR2GRAY);
		return grayIm.clone();
	}
	else
	{
		grayIm = im;
		return grayIm.clone();
	}		
}
/**	@brief Method for thresholding of gray image. There are two methods witch are implemented. Default is Canny with histeresis.
*	Second option is second derivate with thresh.
*	Before edges image is equalized and for noise reduction convoled by gaussian.
*	@param im: Gray image
*	@param UseCannyThreshold: True = Canny / False = second derivation
*	@out Parametric image later used for contours finding
*/
Mat imadjust::imThresh(Mat & im, bool UseCannyThreshold)
{	
	double sigma = 0.33;	// 0.33 This parameter determine how many % with middle in median image will be used for canny hysteresis
	
	double med = medianMat(im);
	//Adaptive kernel size for operations from 3-7 based on resoluction
	int KernelSize = (int)Scale * 3;
	if (KernelSize % 2 == 0)
		KernelSize += 1;
	if (KernelSize > 7)
		KernelSize = 7;
	else if (KernelSize < 3)
		KernelSize = 3;

	equalizeHist(im, im);
	//noise reduction		
	GaussianBlur(im, im, Size(3, 3), KernelSize, KernelSize);
	if (UseCannyThreshold)
	{				
		//Set thresholds
		int lower = (1 - sigma) * med;
		int upper = (1 + sigma) * med;
		Canny(im, im, lower, upper,KernelSize);			
	}
	else
	{		
		Mat LapIm;
		Laplacian(im, LapIm, CV_64F, KernelSize);

		double min, max;
		minMaxLoc(LapIm, &min, &max);

		LapIm = LapIm > (max * 0.1);			
		convertScaleAbs(LapIm, im);
		RemoveStandAlonePixels(im);		
	}	
	return im;
}
/**	@brief Method for finding median from image
*	@param Im: Gray image
*	@out: median
*/
double imadjust::medianMat(cv::Mat Im) {
		double m = (Im.rows*Im.cols) / 2;
		int bin = 0;
		double med = -1.0;

		int histSize = 256;
		float range[] = { 0, 256 };
		const float* histRange = { range };
		bool uniform = true;
		bool accumulate = false;
		cv::Mat hist;
		cv::calcHist(&Im, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange, uniform, accumulate);

		for (int i = 0; i < histSize && med < 0.0; ++i)
		{
			bin += cvRound(hist.at< float >(i));
			if (bin > m && med < 0.0)
				med = i;
		}
		return med;
}

/**	@brief Remove pixels witch are surounded by zero pixels
*	@param im: input bw image
*	@out: filtered image
*/
Mat imadjust::RemoveStandAlonePixels(Mat & im)
{		
	Mat kernel = (Mat_<bool>(3, 3) <<
		1, 1, 1,
		1, 0, 1,
		1, 1, 1);
	Mat conv;
	filter2D(im, conv, CV_8U, kernel);	
	bitwise_and(im, conv,im);
	return im;
}
/**	@brief Worker method for image preprocesing, each method is step
*	@param im: input image from camera
*	@out: adjusted image ready for contours finding
*/
Mat imadjust::doWork(Mat & im)
{
	Mat ImAdjusted;
	ImAdjusted = im2gray(im);
	ImAdjusted = imThresh(ImAdjusted,EDGE);
	return ImAdjusted;
}
