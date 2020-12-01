#include "Canvas.h"
#include <algorithm>

Canvas::Canvas(int a, int b) {

	width_ = a;
	height_ = b;

	pixels = new Color[width_ * height_];
	for (int i = 0; i < height_; i++) {
		for (int j = 0; j < width_; j++) {
			pixels[i * width_ + j] = Color();
		}
	}
}

Canvas::Canvas(const Canvas& c) {

	width_ = c.width_;
	height_ = c.height_;

	pixels = new Color[width_ * height_];
	for (int i = 0; i < height_; i++) {
		for (int j = 0; j < width_; j++) {
			pixels[i * width_ + j] = Color(c.pixels[i * width_ + j]);
		}
	}

}

Color Canvas::getPixel(int x, int y) {
	return pixels[x + y * width_];
}

void Canvas::writePixel(int x, int y, Color c) {
	
	c.clampRGB();
	pixels[x + y * width_] = c;

}

double Canvas::round(double a) {
	return floor(a + 0.5);
}

std::string Canvas::toPPM() {

	std::string str;
	str += "P3\n";
	str += std::to_string(width_) + ' ';
	str += std::to_string(height_) + '\n';
	str += "255\n";

	for (int i = 0; i < height_; i++) {

		std::string line;
		int len = 0;

		for (int j = 0; j < width_; j++) {

			int index = i * width_ + j;
			Color c = pixels[index];
			std::string red = std::to_string((int)round(c.red() * 255));
			std::string green = std::to_string((int)round(c.green() * 255));
			std::string blue = std::to_string((int)round(c.blue() * 255));

			int redl = red.length();
			int greenl = green.length();
			int bluel = blue.length();

			if (len == 0) line += red;
			else if (len + 1 + redl <= 70) line += ' ' + red;
			else {
				line += '\n' + red + ' ' + green + ' ' + blue;
				len = redl + 1 + greenl + 1 + bluel;
				continue;
			}
			if (len == 0) len += redl; 
			else len += 1 + redl;
			
			if (len + 1 + greenl <= 70) line += ' ' + green;
			else {
				line += '\n' + green + ' ' + blue;
				len = greenl + 1 + bluel;
				continue;
			}
			len += 1 + greenl;
			
			if (len + 1 + bluel < 70) line += ' ' + blue;
			else if (len + 1 + bluel == 70) {
				line += ' ' + blue + '\n';
				len = 0;
				continue;
			}
			else {
				line += '\n' + blue;
				len = bluel;
				continue;
			}
			len += 1 + bluel;

		}

		line += '\n';
		str += line;
	}

	return str;
}