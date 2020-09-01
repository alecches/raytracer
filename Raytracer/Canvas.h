#pragma once
#include "Color.h"

class Canvas
{
private:	
	Color* pixels;

public:
	int width, height;
	Canvas(int, int);
	Color getPixel(int, int);
	void writePixel(int, int, Color);
};

