#pragma once
#include "../property/Color.h"
#include "../world/Ray.h"
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

	// new for multithreading
	Color& getPixelRef(int x, int y);
};


struct Pixel {
	Ray r;
	Color c;
};

// a temporary class for testing multithreaded render
class Canvas2 {
private:
	Pixel* pixels;
	int width_, height_;
	int nextPixel;

public:

	Canvas2(int, int);
	Canvas2(const Canvas2&);
	~Canvas2() { delete pixels; };
	int width() const { return width_; }
	int height() const { return height_; }

	Color getPixel(int, int);
	void writePixel(int, int, Color);
	std::string toPPM();
	double round(double);

	void assignRay(int, int, Ray);
	Pixel* getPixelRef();

};