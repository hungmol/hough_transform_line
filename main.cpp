#include "HoughTransformLine.h"

int main()
{
	HoughTransformLine lineDetection("test3.jpg");
	lineDetection.detectLine();
    std::cout << "Hello World!\n";
}

