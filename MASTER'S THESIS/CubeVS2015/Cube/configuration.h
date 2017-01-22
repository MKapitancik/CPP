#pragma once
//#define WINDOWS
//#define LINUX

/**
*	camera settings
*/
///GLOBAL CAM SETINGS
#define CAMERA
#define DIRPATH "c:\\Maros\\Vysoka skola\\Diplomka\\Testy\\PrilohyVyber"
#define EDGE 1
#define CAMWIDTH 800
#define CAMHEIGHT 600
#define pixels CAMWIDTH * CAMHEIGHT

/**
*	imadjust
*/
#define Scale sqrt(pixels)/1000
/**
*	getsegments
*/
//Minimum deviation for segmentated images before they are encapsulated to the segment class
#define MINDEV 15	
///Exiting this area segments will not be accepted computed from size of grabed image
#define MINAREA 100		//10x10
#define MAXAREA Scale*50000

#define RADT 0.6	//0.6 variance between dot product cosinus, we are looking for propendicular angles witch means 0 radians.. +- RADT

///for debug
#define EPSILON 0.03

/**
*	mark
*/
//Size of mark in pixels (has to be same as size of segments)
#define MARKSIZE 120
//Number of "binary" pixels including border
#define MARKPIXS 6

/**
*	templatematch
*/
//Margin of block images from segments 1 means that segment will be 1px from each side smaller than before
#define MARGIN 4
//When exiting difference(comparing each block with each) than segment is market as different
#define MAXDIFF 2

