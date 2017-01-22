#include "getsegments.h"
using namespace cv;

/**	@brief Default C�tor inicialize transform image by default size.
*/
getsegments::getsegments()
{
	transform = Mat::zeros(Size(MARKSIZE, MARKSIZE), CV_8U);
}
/**	@brief C�tor with wich can be set transformation image size(also output image size from this class)
*/
getsegments::getsegments(Size outImSize)
{
	transform = Mat::zeros(outImSize, CV_8U);
}
/** @brief D�tor
*/
getsegments::~getsegments()
{
	contours.clear();
	rectApprox.clear();
	segments.clear();
	approx.clear();
}
/** @brief This metod clear alocated vectors before they are used again
*/
void getsegments::cleanBeforeUse()
{
	contours.clear();
	rectApprox.clear();
	segments.clear();
	approx.clear();
}
/** @brief Get dot-product of three points
*	https://www.mathsisfun.com/algebra/vectors-dot-product.html
*	@param pt0-2: input points
*	@out: dot-product in radians
*/
static double angle(cv::Point pt1, cv::Point pt2, cv::Point pt0)
{
	double dx1 = pt1.x - pt0.x;
	double dy1 = pt1.y - pt0.y;
	double dx2 = pt2.x - pt0.x;
	double dy2 = pt2.y - pt0.y;
	return (dx1*dx2 + dy1*dy2) / sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

/**	@brief Finds contours in input image, next step is aproximation of this contorus. If contorus meets all requirements
*	thease are: 4 sided object, size of area, convex, then are saved into rectApprox for next evaluation
*	@param im: adjusted image from class imadjust (bw image)
*/
void getsegments::findContour(Mat im, Mat origIm, Mat drawImg)
{
	Mat debugVisualisation;
	cvtColor(drawImg, debugVisualisation, CV_GRAY2BGR);

	/*
	//contour RGB visualisation for debug
	std::vector<cv::Vec4i> hierarchy;
	findContours(im.clone(), contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	Mat outImage = Mat::zeros(im.rows,im.cols,CV_8UC3);
	if (!contours.empty() && !hierarchy.empty()) {

		// loop through the contours/hierarchy
		for (int i = 0; i<contours.size(); i++) {

				Scalar colour((rand() & 255), (rand() & 255), (rand() & 255));
				drawContours(outImage, contours, i, colour);
		}
	}
	imshow("contour", outImage);
	waitKey();
	*/

	findContours(im.clone(), contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
	//CV_CHAIN_APPROX_SIMPLE compresses horizontal, vertical, and diagonal segments and leaves only their end points.
	cvtColor(im, im, CV_GRAY2BGR);
	for (int i = 0; i < contours.size(); i++)
	{		
		if (contours[i].size() < 4)
			continue;

		double contoursize = fabs(contourArea(contours[i]));
		if (contoursize < MINAREA || contoursize > MAXAREA)	//MINAREA & MAXAREA definied in header
			continue;
		approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*EPSILON, true);	// for debug
		
		//if approx have 4 sides it is either debugVisualisation square or debugVisualisation rectangle
		if (approx.size() == 4)
		{					
			if (!cv::isContourConvex(approx))
				continue;

			// Get the cosines of all corners
			std::vector<double> cos;
			for (int j = 2; j < approx.size() + 1; j++)
				cos.push_back(angle(approx[j%approx.size()], approx[j - 2], approx[j - 1]));

			// Sort ascending the cosine values
			std::sort(cos.begin(), cos.end());

			// Get the lowest and the highest cosine
			double mincos = cos.front();
			double maxcos = cos.back();

			if (mincos >= -RADT && maxcos <= RADT)
			{
				
				// FOR DEBUG
				//WARNING BRINGS LINES TO NEW IMAGE	
				auto col = CV_RGB(0, 0, 255);
				
				line(debugVisualisation, approx[0], approx[1], col, 2);
				line(debugVisualisation, approx[1], approx[2], col, 2);
				line(debugVisualisation, approx[2], approx[3], col, 2);
				line(debugVisualisation, approx[3], approx[0], col, 2);				
				// save good approximation points
				rectApprox.push_back(vector<Point2f>(approx.begin(), approx.end()));				
			}
		}	
	}
}
/**	@brief Method for shorting corners to proper order. This must be done before perspective transformation
*	otherwise the transformations will not match definied corners and image will be deformed
*	@param corners: unshorted vector of points (corners)
*	@out: shorted corners
*/
vector<Point2f> getsegments::sortCorners(vector<Point2f>& corners)
{
	Point2f center(0, 0);
	//get center of corners simply doing mean
	for (int i = 0; i < corners.size(); i++)
		center += corners[i];

	vector<Point2f> newCorners = corners;
	center *= (1. / corners.size());

	std::vector<cv::Point2f> top, bot;

	//Divide to top or bottom from center by height
	for (int i = 0; i < newCorners.size(); i++)
	{
		if (newCorners[i].y < center.y)
			top.push_back(newCorners[i]);
		else
			bot.push_back(newCorners[i]);
	}

	newCorners.clear();

	//divide to left of right by width
	if (top.size() == 2 && bot.size() == 2) {
		cv::Point2f tl = top[0].x > top[1].x ? top[1] : top[0];
		cv::Point2f tr = top[0].x > top[1].x ? top[0] : top[1];
		cv::Point2f bl = bot[0].x > bot[1].x ? bot[1] : bot[0];
		cv::Point2f br = bot[0].x > bot[1].x ? bot[0] : bot[1];
		//save shorted corners
		newCorners.push_back(tl);
		newCorners.push_back(tr);
		newCorners.push_back(br);
		newCorners.push_back(bl);
	}
	return newCorners;
}
/** @brief Perspective transformation of image to get final segment image from original image.
*	This metod compute transfomation image for every finded rectangle in image and save it to segment class witch encapsulate several informations
*	@param origIm: Original image from witch will be transformation computed
*	@param corners: vector of vectors with finded corners from approximation
*	@out: vector of segments class for all finded segments
*/
vector<segment> getsegments::persTransf(Mat &origIm, vector<vector<Point2f>> corners)
{
	for (int i = 0; i < corners.size(); i++)
	{
		vector<Point2f> ShortedCorners = sortCorners(corners[i]);
		/* FOR DEBUG
		line(origIm, corners[i][0], corners[i][1], Scalar(255), 1);
		line(origIm, corners[i][1], corners[i][2], Scalar(255), 1);
		line(origIm, corners[i][2], corners[i][3], Scalar(255), 1);
		line(origIm, corners[i][3], corners[i][0], Scalar(255), 1);
		*/
		//Sometimes ShortedCorners fails so this condition is only for this purposes
		if (ShortedCorners.size() > 0)
		{
			// Declaration of new corners positions
			std::vector<cv::Point2f> NewCorners;
			NewCorners.push_back(cv::Point2f(0, 0));
			NewCorners.push_back(cv::Point2f(transform.cols, 0));
			NewCorners.push_back(cv::Point2f(transform.cols, transform.rows));
			NewCorners.push_back(cv::Point2f(0, transform.rows));
			
			//Getting transformation matrix
			cv::Mat transmtx = cv::getPerspectiveTransform(ShortedCorners, NewCorners);

			//Perspective transformation of original image to custom sized image
			cv::warpPerspective(origIm, transform, transmtx, transform.size());
			//cv::warpPerspective(origIm, transform, transmtx, transform.size(),CV_INTER_NN);

			//Check if image have required minimum deviation
			Mat mean, dev;
            meanStdDev(transform, mean, dev);
			double ddev = dev.at<double>(0);
			if (ddev > MINDEV)
			{
				//Encapsulate image and default corners from original image to segment class
				segments.push_back(segment(transform, ShortedCorners));
			}
		}
	}
	return segments;
}
/**	@brief Worker method for image segmentation, each method is step
*	@param bwIm: Adjusted image from imadjust class
*	@param origIm: original BGR or Gray image
*	@out: finded vector of segmetns from image
*/
vector<segment> getsegments::doWork(Mat bwIm, Mat origIm)
{
	cleanBeforeUse();
	findContour(bwIm,origIm, origIm.clone());
	persTransf(origIm, rectApprox);
	return segments;
}
/**	@brief Return finded segments from image in one Mat
*/
Mat getsegments::getMatofSegments()
{
	if (segments.size() > 0)
	{
		int r = 0;
		int c = 0;
		int sSize = segments.size();
		if (sSize / 4 == 0)
		{
			c = sSize % 4;
			r = 1;
		}
		else
		{
			c = 4;
			int zv = sSize % 4;
			r = sSize / 4;
			if (zv)
				r += 1;
		}

		int rw = r * (MARKSIZE + 10);
		int cl = c * (MARKSIZE + 10);
		Mat SShow = Mat::zeros(rw, cl, CV_8U);

		int row = 0, col = 0;
        for (int c = 0; c < segments.size();)
		{
			segments[c].getFrame().copyTo(SShow(Rect(col, row, MARKSIZE, MARKSIZE)));
			col += MARKSIZE + 10;

			c++;
			if (c % 4 == 0)
			{
				row += MARKSIZE + 10;
				col = 0;
			}
		}
		return SShow;
	}
	return Mat();
}

