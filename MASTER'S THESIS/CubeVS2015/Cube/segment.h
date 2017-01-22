#pragma once
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "configuration.h"

using namespace std;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*	@brief Trieda pre zapuzdrenie najdeneho kandidata v obraze, taktiez velkost plochy, indikujucej vzdialenost, ID je pridelene ak sa segment zhoduje s markerom.
*	Tomuto ID nasledne bude mozne priradit pozadovanu operaciu pre vykonanie robotom
*/
class segment
{	
	cv::Mat seg;			//Image of segment perspective transformed
	cv::Mat bwSeg;			//BW image of segment
	double area;		//Area of segment in original image
	int diff = -1;		//Counts diference from mark in "imaginary pixel" by default -1. Diff is assigned by templatematch class. 
	int ID = -1;		//ID= -1 by default, if match with marker is found ID = mark.id
	vector<cv::Point2f> origCorners;	//Location of original corners in input image
public:		
	///C´tors
	segment(cv::Mat &im, vector<cv::Point2f> corners);
	///Methods
	cv::Mat getFrame();
	cv::Mat getBwFrame();
	cv::Mat getResized(cv::Size changeSegmentSize);	//Get mark of custom size	
	cv::Mat getResizedBW(cv::Size changeSegmentSize);	//Get bw mark of custom size	
	double GetArea() const { return contourArea(origCorners); }	//compute area of segment from position of corners in original image (original size)
	int GetDiff() const { return diff; }
	void SetDiff(const int difference);
	vector<cv::Point2f> getCorners() { return origCorners; }
	void SetId(const int id);
	int GetId() const;
	///D´tor
	~segment();
};

