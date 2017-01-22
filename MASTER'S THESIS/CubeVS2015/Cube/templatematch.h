#pragma once
#include <string>
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "configuration.h"
#include "mark.h"
#include "segment.h"

using namespace std;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*	@brief Trieda pre zapuzdrenie najdeneho kandidata v obraze, taktiez velkost plochy, indikujucej vzdialenost, ID je pridelene ak sa segment zhoduje s markerom.
*	Tomuto ID nasledne bude mozne priradit pozadovanu operaciu pre vykonanie robotom
*/
class templatematch
{
	vector<mark> templates;		//vector of mark class witch contains mark image, id and another informations 
	vector<segment> segments;	//vector of finded ROI in image, segment class contains information about ROI
public:
	///C´tors
	templatematch();	//Default C´tor wich contains user definied marks pushed to templates vector
	///Methods
	void Match(segment& segm); //Matcher method witch compare segmetn witch templates
	void rot90(mark& mk, int rotflag);	//Fast rotation of image	
	void stampIfSame(mark& mk, segment& segm);	//If segment=mark then id of mark is set to segment id
	void findNearlest(mark& mk, segment& segm, int same);	//Set id of segments witch are looking like some of mark, but there is small diference
	cv::Mat subdivide(const cv::Mat &img, const int Divisor, const int margin = 0);	//Fast subdivide witch return Mat of divided image
	int Compare(cv::Mat &Segment, cv::Mat &Template); //Compare segment witch template, input mat are divided mat from subdivide method	
	void DrawFinded(cv::Mat& origIm);	//Draw matched segments with mark to image, removing dubplicities
	vector<segment> doWork(vector<segment>& segments, cv::Mat &image);	//Worker method
	///D´tor
	~templatematch();
};