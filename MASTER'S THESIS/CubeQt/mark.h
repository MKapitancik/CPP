#pragma once
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "configuration.h"

using namespace std;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**	@brief Trieda pre vytvaranie sablon, pre vytvorenie ARTagu je nutne vyuzit konstruktor marker(Mat &im), vstupny obraz je iba binarny kod,
*	konstruktor ohranici marker ciernou oblastou. ID ktore je priradene markeru je rovne poctu zijucich markerov, alebo uzivatelom specifikovane.
*/
class mark
{		
	static int count;		//determine how many marks are created, also by default sets mark id, (id = ++count)
	cv::Mat mk;					//binnary image of mark	
	int id;					//mark id	
	cv::Mat createMark(const cv::Mat& binMark);		//Border mark wiht black pixels around	
public:
	///C´tors
	mark();					//does nothing 	
	mark(cv::Mat& im);			//Use to create mark, input image is without border
	mark(cv::Mat& im, int ID);	//With user definied ID
	///Methods
	cv::Mat getImg();			//Get marker image by reference
	int getId();			//Get marker ID	
	cv::Mat getResized(cv::Size changeMarkSize);	//Get mark of custom size	
	void showMark();		//Show mark in window named by mark ID
	///D´tor
	~mark();				//D´tor
};