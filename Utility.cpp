#include "Utility.h"

bool Utility::edgeDetection(string imageName, Mat &outEdge) {
	if (!isFileExist(imageName)) {
		cerr << "[ERROR] File not found!\n";
		return false;
	}
	try {
		// Read image
		Mat image = imread(imageName, IMREAD_COLOR);
		Mat grayImg;
		// Convert to gray image 
		if (image.channels() > 1) {
			cvtColor(image, grayImg, COLOR_RGB2GRAY);
		}
		else {
			grayImg = image.clone();
		}
		// Smooth image with Gaussian filter
		Mat blurImg;
		GaussianBlur(grayImg, blurImg, cv::Size(5, 5), 0, 0); // Kernel 5x5 as usual

		// Canny Edge detection
		Canny(blurImg, outEdge, LOW_CANNY_THRESH, HIGH_CANNY_THRESH);
		return true;
	}
	catch (cv::Exception & err) {
		cerr << "[ERROR] " << err.what() << endl;
	}
	return false;
}

bool Utility::edgeDetection(Mat inputImage, Mat& outEdge) {
	if (!inputImage.data) {
		cerr << "[ERROR] Invalid input image!\n";
		return false;
	}
	try {
		// Read image
		Mat grayImg;
		// Convert to gray image 
		if (inputImage.channels() > 1) {
			cvtColor(inputImage, grayImg, COLOR_RGB2GRAY);
		}
		else {
			grayImg = inputImage.clone();
		}
		// Smooth image with Gaussian filter
		Mat blurImg;
		GaussianBlur(grayImg, blurImg, cv::Size(5, 5), 0, 0); // Kernel 5x5 as usual

		// Canny Edge detection
		Canny(blurImg, outEdge, LOW_CANNY_THRESH, HIGH_CANNY_THRESH);
		return true;
	}
	catch (cv::Exception & err) {
		cerr << "[ERROR] " << err.what() << endl;
	}
	return false;
}

bool Utility::isFileExist(string file_name) {
	try {
		fs::path pathObj(file_name);
		if (fs::exists(pathObj) && fs::is_regular_file(pathObj)) {
			return true;
		}
	}
	catch (fs::filesystem_error & err) {
		cerr << "[ERROR] " << err.what() << endl;
	}
	return false;
}

bool Utility::isPathExist(string file_path) {
	try {
		fs::path pathObj(file_path);
		if (fs::exists(pathObj) && fs::is_directory(pathObj)) {
			return true;
		}
	}
	catch (fs::filesystem_error & err) {
		cerr << "[ERROR] " << err.what() << endl;
	}
	return false;
}
