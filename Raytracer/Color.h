#pragma once
class Color
{
public:
	double red, green, blue;
	Color();
	Color(double, double, double);
	
	Color operator+(Color);
	Color operator-(Color);
	Color operator*(Color);
	Color operator*(double);
	bool operator==(Color);

	double clamp(double);
	void clampRGB();
};

