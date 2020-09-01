#include "Canvas.h"

Canvas::Canvas(int a, int b) {

	width = a;
	height = b;

	pixels = new Color[width * height];
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			pixels[i * height + j] = Color();
		}
	}
}

Color Canvas::getPixel(int x, int y) {
	return pixels[x * height + y];
}

void Canvas::writePixel(int x, int y, Color c) {
	pixels[x * height + y] = c;
}