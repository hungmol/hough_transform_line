#pragma once

#include "Utility.h"

// This class only implement Hough transform standard only found infinite lines

//TO-DO: implement probabilisitc Hough Line transform for finite lines

class HoughTransformLine
{
public:
	HoughTransformLine();
	HoughTransformLine(string _filename) {
		this->fileName = _filename;
	};

	//~HoughTransformLine();
	bool detectLine();
	bool drawHoughLine(Mat& outputImage);

private:
	string fileName;
	string filePath;
	Mat image;
	Mat edgeImage;
	int image_width;
	int image_height;

	// Theta from [-Pi/2, Pi/2] or [-90, 90], r = costheta)*x + sin(theta)*y
	map<vector<int>, int> accumulator;
	map<vector<int>, int> strongHoughLines;

	bool removeWeakLine();
};

