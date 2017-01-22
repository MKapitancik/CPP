#pragma once
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "configuration.h"
#include "segment.h"

using namespace std;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*	@brief Trieda pre segmentaciu oblasti ktore maju tvar stvorca medzi minimalnou a maximalnou velkostou plochy splnajuce tak kriteria pre moznych kandidatov
*	Najprv sa urcia kontury oblasti a nasledne sa aproximuje polynom, v pripade ze ma stvorcovy tvar je pridany do vektoru segmentov
*/
class getsegments
{
	cv::Mat transform;		//Image for storing transformation. Size of this image will be used as trasnformation final image size (Size can be definied by using proper constructor) 
	vector<vector<cv::Point>> contours;	//Store for finded contorus
	vector<cv::Point2f> approx;			//Store for approximation of contour
	vector<vector<cv::Point2f>> rectApprox;	//Store for rectangle approximations
	vector<segment> segments;		//Store for finded segmetns from image	 	
public:
	///C´tors
	getsegments();					//By default create zeros transform image Size(200,200)
	getsegments(cv::Size outImSize);	//Custom size of transform image can be set by this Ctor
	///Methods	
	void cleanBeforeUse();			//Because during this class are used vectors for storing contours, segments etc, all must be cleaned each cycle (to remove duplicate)
    void findContour(cv::Mat im, cv::Mat origIm, cv::Mat drawImg);		//Compute contour of image storing imformations in private variables
	vector<cv::Point2f> sortCorners(vector<cv::Point2f>& corners);		//Sort corners for proper perspective transformation
	vector<segment> persTransf(cv::Mat &origIm, vector<vector<cv::Point2f>> corners);	//Persp. Trasnformation of image, ROI definied by corners
    vector<segment> doWork(cv::Mat bwIm, cv::Mat origIm);	//Worker method
	cv::Mat getMatofSegments();
	///D´tor
	~getsegments();
};
