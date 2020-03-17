#include "HoughTransformLine.h"

bool HoughTransformLine::detectLine() {
	if (!Utility::isFileExist(this->fileName)) {
		cerr << "[ERROR] File not found!\n";
		return false;
	}
	this->image = imread(this->fileName, IMREAD_COLOR);
	if (!this->image.data) {
		cerr << "[ERROR] Could not load the image\n";
		return false;
	}
	// Edge detection
	
	if (!Utility::edgeDetection(this->image, this->edgeImage))
		return false;
	imshow("edgeTest", this->edgeImage);
	waitKey(500);

	this->image_width = this->edgeImage.cols;
	this->image_height = this->edgeImage.rows;

	// Convert to Hough normal space
	// Theta range from [0, 360] and r > 0
	for (int y = 0; y < this->edgeImage.rows; y++) {
		uchar* ptr = this->edgeImage.data + y * this->edgeImage.cols;
		for (int x = 0; x < this->edgeImage.cols; x++, ptr++) {
			if (*ptr > 0) {
				for (int theta = 0; theta <= 180; theta++) {
					float theta_radian = M_PI * theta / 180;
					int r = (int)(x * cos(theta_radian) + y * sin(theta_radian));
					vector<int> tmp{ r, theta };
					accumulator[tmp] += 1;
				}
			}
			else
				continue;
		}
	}

	cout << "Remove weak lines" << endl;
	removeWeakLine();
	//// Print out all accumulator for testing
	//map<vector<int>, int>::iterator itr;
	//for (itr = strongHoughLines.begin(); itr != strongHoughLines.end(); ++itr) {
	//	cout << "\t" << itr->first[0] << " " << itr->first[1]
	//		<< "\t" << itr->second << endl;
	//}

	cout << "Draw hough line\n";
	drawHoughLine(this->image);
	imshow("output", this->image);
	waitKey(0);
	return true;
}

bool HoughTransformLine::removeWeakLine() {
	// Find the max voting
	unsigned int currentMax = 0;
	map<vector<int>, int>::iterator itr;
	for (itr = this->accumulator.begin(); itr != this->accumulator.end(); ++itr) {
		itr->second > currentMax ? currentMax = itr->second : currentMax = currentMax;
	}

	int threshold = RATIO * currentMax;
	
	for (itr = this->accumulator.begin(); itr != this->accumulator.end(); ++itr) {
		if (itr->second >= threshold) {
			this->strongHoughLines.insert(pair<vector<int>, int>(itr->first, itr->second));
		}
	}
	
	return true;
}

bool HoughTransformLine::drawHoughLine(Mat &outputImage) {
	map<vector<int>, int>::iterator it;
	for (it = this->strongHoughLines.begin(); it != this->strongHoughLines.end(); ++it) {
		Point fstPoint;
		Point sndPoint;
		fstPoint.x = 0;
		sndPoint.x = this->image_width - 1;
		float theta_radian = M_PI * it->first[1] / 180;
		float r = it->first[0];
		fstPoint.y = -fstPoint.x * cos(theta_radian) / sin(theta_radian) + r / sin(theta_radian);
		sndPoint.y = -sndPoint.x * cos(theta_radian) / sin(theta_radian) + r / sin(theta_radian);
		line(outputImage, fstPoint, sndPoint, Scalar(0, 255, 0), 2, LINE_AA);
	}
	return true;
}