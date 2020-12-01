#pragma once
class Color
{
private:
	double red_, green_, blue_;
public:
	
	Color() : red_{ 0 }, green_{ 0 }, blue_{ 0 } {}
	Color(double r, double g, double b) : red_{ r }, green_{ g }, blue_{ b } {}
	Color(const Color& c) :red_{ c.red() }, green_{ c.green() }, blue_{ c.blue() } {}
	double red() const { return red_; }
	double green() const { return green_; }
	double blue() const { return blue_; }

	Color operator+(const Color&) const;
	Color operator-(const Color&) const;
	Color operator*(const Color&) const;
	Color operator*(double) const;
	bool operator==(const Color&) const;

	void clampRGB();
};

double clamp(double);

