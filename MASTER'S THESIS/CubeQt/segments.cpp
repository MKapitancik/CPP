#include "segment.h"
using namespace cv;
/**	@brief C´tor for segment class, also compute original image area of segment from corners 
*	for segmentation is used Otsu thresh as image whitch is mark has two peaks black and yellow.
*	@input im: From perspective transformation can be BGR or gray
*	@input corners: vector of original corners in image	
*/
segment::segment(Mat & im, vector<Point2f> corners)
{
	Mat eq;
	if (im.channels() == 3)
		cvtColor(im, seg, CV_BGR2GRAY);
	else
		seg = im.clone();
	threshold(seg, bwSeg, 0, 255, CV_THRESH_OTSU);
	origCorners = corners;
	area = fabs(contourArea(corners));		
}
/**	@brief Return original segment image used in constructor
*/
Mat segment::getFrame()
{
	return seg;
}
/**	@brief Return bw segmented iamge
*/
Mat segment::getBwFrame()
{
	return bwSeg;
}
/**	@brief Return resized segment image
*	@param changeSegmentSize: User definied size of image to return
*	@out: resized image
*/
Mat segment::getResized(Size changeSegmentSize)
{
	if (!seg.empty())
	{
		Mat resized;
		resize(seg, resized, changeSegmentSize, 0, 0, INTER_NEAREST);
		normalize(resized, resized, 0, 255, NORM_MINMAX);
		return resized;
	}
	else
	{
		return seg;
	}
}
/**	@brief Return resized segment bw image
*	@param changeSegmentSize: User definied size of image to return
*	@out: resized image
*/
Mat segment::getResizedBW(Size changeSegmentSize)
{
	if (!seg.empty())
	{
		Mat resized;
		resize(bwSeg, resized, changeSegmentSize, 0, 0, INTER_NEAREST);
		normalize(resized, resized, 0, 255, NORM_MINMAX);
		return resized;
	}
	else
	{
		return bwSeg;
	}
}
/**	@brief Set diference in imaginary "pixels" of segment from close mark template
*	@param difference: diference from templatematch class
*/
void segment::SetDiff(const int difference)
{
	if (difference < diff || diff == -1)
		diff = difference;		
}
/**	@brief Set ID of segment if match witch marker is finded or marker is closer with diff as definied in templatematch class
*	@param id: segment ID
*/
void segment::SetId(int id)
{
	ID = id;
}
/**	@brief Get id of segment
*/
int segment::GetId() const
{
	return ID;
}
/**	@brief D´tor
*/
segment::~segment()
{
}
