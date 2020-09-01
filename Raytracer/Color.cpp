#include "Color.h"
#include <cmath>

Color::Color() {
	red = 0.0;
	green = 0.0;
	blue = 0.0;
}

Color::Color(double a, double b, double c) {
	red = a;
	green = b;
	blue = c;
}

bool Color::operator==(Color c) {
	const double E = 0.00001;

	if (abs(red - c.red) > E) return false;
	if (abs(green - c.green) > E) return false;
	if (abs(blue - c.blue) > E) return false;
	return true;
}


Color Color::operator+(Color c2) {
	Color c;
	c.red = red + c2.red;
	c.green = green + c2.green;
	c.blue = blue + c2.blue;

	return c;
}

Color Color::operator-(Color c2) {
	Color c;
	c.red = red - c2.red;
	c.green = green - c2.green;
	c.blue = blue - c2.blue;

	return c;
}

Color Color::operator*(Color c2) {
	Color c;
	c.red = red * c2.red;
	c.green = green * c2.green;
	c.blue = blue * c2.blue;

	return c;
}

Color Color::operator*(double scalar) {
	Color c;
	c.red = red * scalar;
	c.green = green * scalar;
	c.blue = blue * scalar;

	return c;
}
