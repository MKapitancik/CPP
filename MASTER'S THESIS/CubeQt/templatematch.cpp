#include "templatematch.h"
using namespace cv;

/**	@brief User definied mark withoud border pixels,
*	witch will be encapsulated in mark class then pushet to templates of this class in default C´tor
*/
#pragma region MARKS 
Mat mark0 = (Mat_<bool>(4, 4) <<
	1, 1, 1, 1,
	1, 0, 0, 1,
	0, 1, 0, 0,
	0, 1, 1, 1);

Mat mark1 = (Mat_<bool>(4, 4) <<
	0, 1, 1, 1,
	1, 0, 0, 1,
	0, 1, 0, 0,
	1, 1, 1, 1);

Mat mark2 = (Mat_<bool>(4, 4) <<
	1, 1, 1, 0,
	1, 0, 0, 1,
	0, 1, 0, 1,
	0, 0, 1, 0);

Mat mark3 = (Mat_<bool>(4, 4) <<
	0, 1, 1, 0,
	1, 0, 0, 1,
	0, 1, 0, 1,
	1, 0, 1, 0);

Mat mark4 = (Mat_<bool>(4, 4) <<
	0, 1, 1, 0,
	1, 0, 0, 1,
	0, 1, 0, 1,
	0, 0, 1, 1);

Mat mark5 = (Mat_<bool>(4, 4) <<
	1, 1, 1, 0,
	1, 0, 0, 1,
	0, 1, 0, 1,
	1, 0, 1, 1);

Mat mark6 = (Mat_<bool>(4, 4) <<
	0, 0, 1, 0,
	0, 1, 0, 1,
	1, 0, 0, 1,
	0, 1, 1, 1);

Mat mark7 = (Mat_<bool>(4, 4) <<
	1, 0, 1, 1,
	0, 1, 0, 1,
	1, 0, 0, 1,
	0, 1, 1, 1);

Mat mark8 = (Mat_<bool>(4, 4) <<
	1, 1, 1, 1,
	1, 0, 0, 1,
	0, 1, 0, 1,
	0, 0, 1, 1);

Mat mark9 = (Mat_<bool>(4, 4) <<
	0, 0, 0, 0,
	0, 1, 0, 0,
	1, 1, 1, 1,
	0, 0, 0, 1);

Mat mark10 = (Mat_<bool>(4, 4) <<
	1, 0, 1, 1,
	1, 1, 0, 0,
	1, 1, 1, 0,
	0, 1, 0, 1);

Mat mark11 = (Mat_<bool>(4, 4) <<
	1, 0, 1, 0,
	0, 1, 0, 0,
	1, 1, 1, 1,
	1, 1, 0, 1);

Mat mark12 = (Mat_<bool>(4, 4) <<
	0, 0, 0, 0,
	0, 1, 0, 0,
	0, 1, 1, 0,
	0, 1, 1, 1);

Mat mark13 = (Mat_<bool>(4, 4) <<
	1, 0, 0, 1,
	0, 1, 0, 0,
	0, 1, 1, 0,
	1, 1, 1, 0);

Mat mark14 = (Mat_<bool>(4, 4) <<
	0, 0, 1, 0,
	0, 1, 0, 0,
	0, 1, 1, 0,
	1, 0, 1, 0);

Mat mark15 = (Mat_<bool>(4, 4) <<
	0, 0, 0, 0,
	1, 1, 1, 0,
	1, 1, 0, 1,
	1, 1, 0, 0);

#pragma endregion

/**	@brief Default C´tor to load definied marks as templates
*/
templatematch::templatematch()
{	
	templates.push_back(mark(mark0, 0));	
	templates.push_back(mark(mark1, 1));
	templates.push_back(mark(mark2, 2));
	templates.push_back(mark(mark3, 3));
	templates.push_back(mark(mark4, 4));	
	templates.push_back(mark(mark5, 5));
	templates.push_back(mark(mark6, 6));
	templates.push_back(mark(mark7, 7));
	templates.push_back(mark(mark8, 8));
	templates.push_back(mark(mark9, 9));
	templates.push_back(mark(mark10, 10));
	templates.push_back(mark(mark11, 11));
	templates.push_back(mark(mark12, 12));
	templates.push_back(mark(mark13, 13));
	templates.push_back(mark(mark14, 14));
	templates.push_back(mark(mark15, 15));		
}
/**	@brief Worker method for template matching
*	@param segments: Vector of segments from getsegments class
*	@param image: original BGR or Gray image
*	@out: matched segments with definied marks
*/
vector<segment> templatematch::doWork(vector<segment>& segments, Mat & image)
{	
	for (auto& segment : segments)
	{
		//Matcher method
		Match(segment);
	}
	templatematch::segments = segments;
	//Draw finded marks to image
	DrawFinded(image);
	return segments;
}
/**	@brief Fast rotation of templates marks based on transposion and flip
*	@param mark: mark class
*	@param rotflag: 1/2/3 90°/180°/270°
*/
void templatematch::rot90(mark &mark, int rotflag) {
	Mat matImage = mark.getImg();

	if (rotflag == 1) {
		transpose(matImage, matImage);
		flip(matImage, matImage, 1); //transpose+flip(1)=90°
	}
	else if (rotflag == 2) {
		flip(matImage, matImage, -1);    //flip(-1)=180          
	}
	else if (rotflag == 3) {
		transpose(matImage, matImage);
		flip(matImage, matImage, 0); //transpose+flip(0)=-90°     
	}
}
/**	@brief Matcher method to compare segment with definied templates ( marks ) 
*	@param segm: segment to compare
*/
void templatematch::Match(segment & segm)
{	
    int same = -1;
	for (auto mark : templates)
	{		
		// get mark image
		Mat image = mark.getImg();
		Mat seg = subdivide(segm.getBwFrame(), MARKPIXS, MARGIN);
		for (int i = 0; i < 4; i++)
		{			
			if(i > 0)
				rot90(mark, 1);
			//divide mark
			Mat templ = subdivide(image, MARKPIXS, MARGIN);
			//compare divided segment and template "samps"
			same = Compare(seg, templ);
			//same = isBlocksSame(templates, segment);
			if (same == 0)
			{
				//asign mark id to segment
				stampIfSame(mark, segm);
				//stop searching
				break;
			}
			else if (same < MAXDIFF)
			{
				//asign mark id if mark is with small diference
				findNearlest(mark, segm, same);
			}
		}
		if (same == 0)
			break;		//if finded stop searching
	}
}
/**	@brief If mark is same than this method asign id of mark to current segment
*	@param mk: mark
*	@param segm: segment witch is same as mark
*/
void templatematch::stampIfSame(mark & mk, segment& segm)
{	
	segm.SetId(mk.getId());	
	segm.SetDiff(0);	//set diference 0 as they are same
}
/**	@brief If mark has little diference when matching than this method is called to determine
*	if there was already asigned any mark or if this mark is closer than mark before	
*	@param mk: mark
*	@param segm: segment witch is nearly same as mark
*	@apram same: as returned number from compare method look there for detailed informations
*/
void templatematch::findNearlest(mark & mk, segment & segm, int same)
{	
	auto diff = segm.GetDiff();
	if (same < diff || diff == -1)
	{
		segm.SetId(mk.getId());
		segm.SetDiff(same);
	}
}
/**	@brief This method draw area of finded marks to input image
*	@param origIm: Original image
*/
void templatematch::DrawFinded(Mat & origIm)
{
	//text settings, scale, font, thickness..
	int fontface = cv::FONT_HERSHEY_SIMPLEX;
	double scale = 0;
	double pix = sqrt(pixels);
	int thickness = (int)pix / 340;

	double del = pix / 1000;
	double meanarea = (MINAREA + MAXAREA) / 2;
	vector<Rect> drawed;	//alocating drawed rectangles for recognition duplicities

	int baseline = 0;	

    for(uint i = 0; i < segments.size(); i++)
	{
		segment segment = segments[i];

		//delete nonmatched segments first ( default ID = -1)
		if (segment.GetId() == -1)
		{
			segments.erase(segments.begin() + i--);
			continue;
		}
		std::ostringstream strs;
		strs << "ID: " << segment.GetId();
		double area = segment.GetArea();
		double uprava = 0.5 / (pix / area - area);
		uprava = area / (area - area / meanarea);
		scale = 0.8 * del * 1 / uprava;
		if (scale < 0)
			scale = 5;
		string str = strs.str();
		//Get bounding box of original corners
		cv::Rect r = cv::boundingRect(segment.getCorners());

		//Lowest the area so nearlest or rotated rectangles dont get touched, this is only for intersection check, so if there is already drawed rectangle
		Rect rr = Rect(r.x + r.width / 4, r.y + r.height / 4, r.width / 2, r.height / 2);
		
		//if segment is good and no intersection with drawed rectangles is finded than draw rectangle
		if (segment.GetDiff() == 0)
		{
			bool intersection = false;
			//Determine if in drawed rectangles is already drawed rectangle (if both rectangles isnt same)
			for (auto rectangles : drawed)
			{
				Rect inter = rectangles & rr;
				if (inter.area() > 0)
				{
					intersection = true;
					//rectangle(origIm, r, CV_RGB(0, 255, 255));	//for debug
					segments.erase(segments.begin() + i--);
					break;
				}
			}
			if (!intersection)
			{
				cv::Size text = cv::getTextSize(str, fontface, scale, thickness, &baseline);

				cv::Point pt(r.x + ((r.width - text.width) / 2), r.y + ((r.height + text.height) / 2));
				rectangle(origIm, r, Scalar(255),2);
				cv::putText(origIm, str, pt, fontface, scale, CV_RGB(0, 255, 0), thickness, 8);
				drawed.push_back(rr);
				continue;
			}
		}
		else if (segment.GetDiff() != -1 && segment.GetDiff() < MAXDIFF)
		{
			cv::Size text = cv::getTextSize(str, fontface, scale, thickness, &baseline);
			//cv::Rect r = cv::boundingRect(segment.getCorners());
			cv::Point pt(r.x + ((r.width - text.width) / 2), r.y + ((r.height + text.height) / 2));
			rectangle(origIm, r, Scalar(200), 2);
			cv::putText(origIm, str, pt, fontface, scale, CV_RGB(200, 0, 0), thickness, 8);
			drawed.push_back(rr);
		}
	}
}
/**	@brief Method witch subdivide input image to definied stamp. It takes four corners witch are margined from side by margin parameter ( 1 margin = 1 pixel from each side)
*	Parameter Divisor must be MARKSIZE%MARKPIX = 0, so it has to be markpix
*  *  *  *  *  *  *  *  *  *			//Example: is 10x10 mark, if input parameter margin is 2 then pixels marked as + are taken
*						   *			//from marked image is created one mat of 2 cols and 3 rows witch is returned
*	  +				 +	   *
*		 		  		   *
*			+	+		   *
*			+  	+		   *
*		 		  		   *
*	  +				 +     *
*						   *
*  *  *  *  *  *  *  *  *  *
@param img: Mark or segment image of size MAKRSIZE
@param Divisor: MARKPIX, imaginary divide mark to "pixels" of mark
@param margin: how much has to be output image margined in pixels
@param out: Mat 2cols*3rows stamp of input image, witch is later compared by compare method
*/
Mat templatematch::subdivide(const cv::Mat & img, const int Divisor, const int margin)
{
	if (img.cols / Divisor < margin)
		cerr << "Margin bigger than image" << endl;

	int sizeX = 4 * (Divisor - 2);
	int sizeY = sizeX / 2;
	int a = 0, b = 1, c = 2, d = 3;

	Mat stamp = Mat::zeros(sizeX, sizeY, CV_8U);
	uchar *stampRow1 = stamp.ptr<uchar>(0);
	uchar *stampRow2 = stamp.ptr<uchar>(1);
	uchar *stampRow3 = stamp.ptr<uchar>(2);
	uchar *stampRow4 = stamp.ptr<uchar>(3);

	if (img.cols % Divisor == 0 && img.rows % Divisor == 0)
	{
		for (int x = img.rows / Divisor + margin; x < img.rows - (img.rows / Divisor); x += img.rows / Divisor)
		{
			//find middle of image with margin
			int Bottom = x - 2 * margin + img.rows / Divisor - 1; // -1 pretoze zaciname od nuly
			int MidRow = ((Bottom - x) - 1) / 2;
			//get pointers to required locations 
			const uchar *TopRow = img.ptr<uchar>(x);
			const uchar *TopMidd = img.ptr<uchar>(x + MidRow);
			const uchar *BotMidd = img.ptr<uchar>(Bottom - MidRow);
			const uchar *BotRow = img.ptr<uchar>(Bottom);

			for (int y = img.cols / Divisor + margin; y < img.cols - (img.cols / Divisor); y += img.cols / Divisor)
			{
				int move = (y - img.cols / Divisor - margin) / (img.cols / Divisor) * 2;
				int RightSide = y - 2 * margin + img.cols / Divisor - 1;
				int MidCol = ((RightSide - y) - 1) / 2;
				//Left top and Right top corner with margin
				uchar TopLeft = TopRow[y];
				uchar TopRiht = TopRow[RightSide];
				//Middle upper left and right
				uchar LeftTopMid = TopMidd[y + MidCol];
				uchar RightTopMid = TopMidd[RightSide - MidCol];
				//Middle lower left and right
				uchar LeftBotMid = BotMidd[y + MidCol];
				uchar RightBotMid = BotMidd[RightSide - MidCol];
				//Bottom left and right corner with margin
				uchar BotLeft = BotRow[y];
				uchar BotRihgt = BotRow[RightSide];

				//feed data
				stampRow1[move] = TopLeft;
				stampRow1[move + 1] = TopRiht;
				stampRow2[move] = LeftTopMid;
				stampRow2[move + 1] = RightTopMid;
				stampRow3[move] = LeftBotMid;
				stampRow3[move + 1] = RightBotMid;
				stampRow4[move] = BotLeft;
				stampRow4[move + 1] = BotRihgt;
			}
			if (x + img.rows / Divisor < img.rows - (img.rows / Divisor))
			{
				stampRow1 = stamp.ptr<uchar>(a += 4);
				stampRow2 = stamp.ptr<uchar>(b += 4);
				stampRow3 = stamp.ptr<uchar>(c += 4);
				stampRow4 = stamp.ptr<uchar>(d += 4);
			}
		}
	}	
	return stamp;
}

/**	@brief D´tor
*/
templatematch::~templatematch()
{
}
/**	@brief Compare two input images from mark and segment subdivide method
*	@param Segment: Subdivided segment image
*	@param Template: Subdivided template image
*/
int templatematch::Compare(Mat & Segment, Mat & Template)
{
	int diff = 0;
	for (int x = 0; x < Segment.rows; x += 4)
	{
		for (int y = 0; y < Segment.cols; y += 2)
		{
			uchar *SegmentRow1 = Segment.ptr<uchar>(x);
			uchar *SegmentRow2 = Segment.ptr<uchar>(x+1);
			uchar *SegmentRow3 = Segment.ptr<uchar>(x+2);
			uchar *SegmentRow4 = Segment.ptr<uchar>(x+3);

			uchar *TemplateRow1 = Template.ptr<uchar>(x);
			uchar *TemplateRow2 = Template.ptr<uchar>(x+1);
			uchar *TemplateRow3 = Template.ptr<uchar>(x+2);
			uchar *TemplateRow4 = Template.ptr<uchar>(x+3);

			int DifferentPixels = 0;
			for (int i = y; i < y + 2; i++)
			{
				SegmentRow1[i] != TemplateRow1[i] ? DifferentPixels++: DifferentPixels;
				SegmentRow2[i] != TemplateRow2[i] ? DifferentPixels++ : DifferentPixels;
				SegmentRow3[i] != TemplateRow3[i] ? DifferentPixels++ : DifferentPixels;
				SegmentRow4[i] != TemplateRow4[i] ? DifferentPixels++ : DifferentPixels;
			}

			if (DifferentPixels > 2 * 4 / 2 )
				diff++;
			if (diff > MAXDIFF)
				break;
		}
		if (diff > MAXDIFF)
			break;
	}
	return diff;
}

