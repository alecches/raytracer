#include "../property/Color.h"
#include <cmath>

double clamp(double a) {

	if (a > 1) return 1;
	if (a < 0) return 0;
	return a;

}

void Color::clampRGB() {
	red_ = clamp(red_);
	green_ = clamp(green_);
	blue_ = clamp(blue_);
}

bool Color::operator==(const Color& c) const {
	const double E = 0.00001;

	if (abs(red_ - c.red_) > E) return false;
	if (abs(green_ - c.green_) > E) return false;
	if (abs(blue_ - c.blue_) > E) return false;
	return true;
}


Color Color::operator+(const Color& c2) const {
	
	double r = red_ + c2.red();
	double g = green_ + c2.green();
	double b = blue_ + c2.blue();

	return Color(r, g, b);
}

Color Color::operator-(const Color& c2) const {

	double r = red_ - c2.red();
	double g = green_ - c2.green();
	double b = blue_ - c2.blue();

	return Color(r, g, b);
}

Color Color::operator*(const Color& c2) const {
	double r = red_ * c2.red();
	double g = green_ * c2.green();
	double b = blue_ * c2.blue();

	return Color(r, g, b);
}

Color Color::operator*(double scalar) const {

	double r = red_ * scalar;
	double g = green_ * scalar;
	double b = blue_ * scalar;

	return Color(r, g, b);
}
