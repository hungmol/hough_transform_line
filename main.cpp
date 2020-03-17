#include "HoughTransformLine.h"

int main()
{
	HoughTransformLine lineDetection("test2.jpg");
	lineDetection.detectLine();
    std::cout << "Hello World!\n";
}

