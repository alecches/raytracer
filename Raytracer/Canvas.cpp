#include "Canvas.h"
#include <algorithm>

Canvas::Canvas(int a, int b) {

	width = a;
	height = b;

	pixels = new Color[width * height];
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			pixels[i * width + j] = Color();
		}
	}
}

Color Canvas::getPixel(int x, int y) {
	return pixels[x + y * width];
}

void Canvas::writePixel(int x, int y, Color c) {
	
	c.clampRGB();
	pixels[x + y * width] = c;

}

double Canvas::round(double a) {
	return floor(a + 0.5);
}

std::string Canvas::toPPM() {

	std::string str;
	str += "P3\n";
	str += std::to_string(width) + ' ';
	str += std::to_string(height) + '\n';
	str += "255\n";

	for (int i = 0; i < height; i++) {

		std::string line;

		for (int j = 0; j < width; j++) {

			int len = line.length() % 70;

			int index = i * width + j;
			Color c = pixels[index];
			std::string red = std::to_string((int)round(c.red * 255));
			std::string green = std::to_string((int)round(c.green * 255));
			std::string blue = std::to_string((int)round(c.blue * 255));

			int redl = red.length();
			if (len == 0) line += red;
			else if (len + 1 + redl < 70) line += ' ' + red;
			else {
				line += '\n' + red + ' ' + green + ' ' + blue;
				continue;
			}
			if (len == 0) len += redl;
			else len += 1 + redl;
			int greenl = green.length();
			if (len + 1 + greenl < 70) line += ' ' + green;
			else {
				line += '\n' + green + ' ' + blue;
				continue;
			}
			len += 1 + greenl;
			int bluel = blue.length();
			if (len + 1 + bluel < 70) line += ' ' + blue;
			else {
				line += '\n' + blue;
			}

		}

		line += '\n';
		str += line;
	}

	return str;
}