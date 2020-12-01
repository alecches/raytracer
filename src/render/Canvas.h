#pragma once
#include "../property/Color.h"
#include <string>

class Canvas
{
private:
	Color* pixels;
	int width_, height_;

public:

	Canvas(int, int);
	Canvas(const Canvas&);
	~Canvas() { delete pixels; };
	int width() const { return width_; }
	int height() const { return height_; }

	Color getPixel(int, int);
	void writePixel(int, int, Color);
	std::string toPPM();
	double round(double);
};

