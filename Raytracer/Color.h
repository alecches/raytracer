#pragma once
class Color
{
private:
	double red_, green_, blue_;
public:
	
	Color() : red_{ 0 }, green_{ 0 }, blue_{ 0 } {}
	Color(double r, double g, double b) : red_{ r }, green_{ g }, blue_{ b } {}
	double red() const { return red_; }
	double green() const { return green_; }
	double blue() const { return blue_; }

	Color operator+(const Color&);
	Color operator-(const Color&);
	Color operator*(const Color&);
	Color operator*(double);
	bool operator==(const Color&);

	void clampRGB();
};

double clamp(double);

