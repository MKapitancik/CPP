#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include "imadjust.h"
#include "getsegments.h"
#include "templatematch.h"
#include "mark.h"
#ifdef WINDOWS
#include <Windows.h>
#endif
#ifdef LINUX
#include <dirent.h>
#include <sys/stat.h>
#endif

using namespace cv;
using namespace std;

void GetFilesInDirectory(std::vector<string> &out, const string &directory)
{
#ifdef WINDOWS
	HANDLE dir;
	WIN32_FIND_DATAA file_data;

	if ((dir = FindFirstFileA((directory + "/*").c_str(), &file_data)) == INVALID_HANDLE_VALUE)
		return; /* No files found */

	do {
		const string file_name = file_data.cFileName;
		const string full_file_name = directory + "/" + file_name;
		const bool is_directory = (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

		if (file_name[0] == '.')
			continue;

		if (is_directory)
			continue;

		out.push_back(full_file_name);
	} while (FindNextFileA(dir, &file_data));

	FindClose(dir);
#endif
#ifdef LINUX
	DIR *dir;
	class dirent *ent;
    class stat st;

    dir = opendir(directory.c_str());
	while ((ent = readdir(dir)) != NULL) {
		const string file_name = ent->d_name;
		const string full_file_name = directory + "/" + file_name;

		if (file_name[0] == '.')
			continue;

		if (stat(full_file_name.c_str(), &st) == -1)
			continue;

		const bool is_directory = (st.st_mode & S_IFDIR) != 0;

		if (is_directory)
			continue;

		out.push_back(full_file_name);
	}
	closedir(dir);
#endif
} // GetFilesInDirectory

int main() {	
	Mat image, adjusted;
	namedWindow("image", WINDOW_NORMAL);
	namedWindow("adjusted", WINDOW_NORMAL);
#ifdef CAMERA
	VideoCapture cap;          //initialize capture
	cap.open(0);
	while (!cap.isOpened());
	cap.set(CV_CAP_PROP_FRAME_WIDTH, CAMWIDTH);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, CAMHEIGHT);
	cout << cap.get(CV_CAP_PROP_FRAME_WIDTH) << "x" << cap.get(CV_CAP_PROP_FRAME_HEIGHT) << endl;
#endif // CAMERA
	//create classes and variables
 	imadjust imadj;
	getsegments getSegment(Size(MARKSIZE, MARKSIZE));
	templatematch match;
	vector<segment> segments;

	vector<string> dirFiles;
	string path = DIRPATH;
	GetFilesInDirectory(dirFiles, path);
	int i = 0;
	while (1) {
#ifdef CAMERA
		cap >> image;          //get data from camera		
#else
		if (i >= dirFiles.size())
			i = 0;
		image = imread(dirFiles[i]);
		i++;
		resize(image, image, Size(CAMWIDTH, CAMHEIGHT));
#endif // CAMERA		
		//compute edge image
		adjusted = imadj.doWork(image);
		//get kandidates from edge image
		segments = getSegment.doWork(adjusted, imadj.GrayIm());	
		//match kandidates with templates
		vector<segment> finded = match.doWork(segments, image);

		imshow("image", image);
		imshow("adjusted", adjusted);
		Mat unitedSegments = getSegment.getMatofSegments();
		if (!unitedSegments.empty())
		{
			imshow("segments", unitedSegments);
		}			
#ifdef CAMERA
		int key = waitKey(5);
		if (key != -1)
			if(key != 255)
				break;
		/*
		if (waitKey(5) >= 0)
			break;          //delay 5ms for opencv imshow	
		*/
#else	
		waitKey();
#endif // CAMERA		
	}
	destroyAllWindows();
	return 0;
}
