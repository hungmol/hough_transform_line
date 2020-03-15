#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <filesystem>

using namespace std;
using namespace cv;

namespace fs = std::filesystem;

#define LOW_CANNY_THRESH 50
#define HIGH_CANNY_THRESH 200

#define M_PI  3.14159265358979323846


class Utility
{

public:
	static bool isFileExist(string file_name);
	static bool isPathExist(string path_name);
	static bool edgeDetection(string imageName, Mat& outEdge);
	static bool edgeDetection(Mat inputImage, Mat& outEdge);

private:
};

