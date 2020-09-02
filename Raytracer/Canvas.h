#pragma once
#include "Color.h"
#include <string>

class Canvas
{
private:
	Color* pixels;

public:
	int width, height;
	Canvas(int, int);
	Color getPixel(int, int);
	void writePixel(int, int, Color);
	std::string toPPM();
	double round(double);
};

