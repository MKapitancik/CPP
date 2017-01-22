#include "mark.h"
using namespace cv;

int mark::count = 0;

mark::mark()
{
}
/*	@brief Set marker image size of MarkSize 
	@param im: Binnary image
*/
mark::mark(Mat & im)
{
	mk = createMark(im);
	mk = getResized(Size(MARKSIZE, MARKSIZE));
	id = count++;
}
mark::mark(Mat & im, int ID)
{
	mk = createMark(im);
	mk = getResized(Size(MARKSIZE, MARKSIZE));
	id = ID;
	//every new id must be bigger than before, for removing potential duplicities
	if (ID < count)
	{
		cout << "ID: " << ID <<
			" musi byt vecsie nez najvecie pouzite: "<< count
			<< " nove id je: " << ++count << endl;
		id = count;
	}
	else
	{
		count = ID;
	}
}
//get marker
Mat mark::getImg()
{
	return mk;
}
//get marker id
int mark::getId()
{
	return id;
}

void mark::showMark()
{
	//show mark in window named by mark ID
	imshow(to_string(id), mk);
}

/*	@brief Border binary image by black pixels, used in constructor
*/
Mat mark::createMark(const Mat & binMark)
{
	mk = Mat::zeros(binMark.rows + 2, binMark.cols + 2, CV_8U);
	binMark.copyTo(mk(Rect(1, 1, binMark.cols, binMark.rows)));
	return mk;
}
//Get resized marker image
Mat mark::getResized(Size changeMarkSize)
{
	if (!mk.empty())
	{
		Mat resized;
		resize(mk, resized, changeMarkSize, 0, 0, INTER_NEAREST);
		normalize(resized, resized, 0, 255, NORM_MINMAX);
		return resized;
	}
	else
	{
		return mk;
	}	
}
//D´tor
mark::~mark()
{
}
