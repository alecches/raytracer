#include <fstream>
#include "Canvas.h"
#include "Color.h"
#include "Matrix.h"
#include "Sphere.h"
#include "TupleFactory.h"
#include "Intersection.h"

using namespace std;


int main() {
	int w = 300, l = 300;
	Canvas c(w, l);

	Sphere s;
	s.transform(scale(100, 100, 1));

	for (int i = 0; i < w; ++i) {
		for (int j = 0; j < l; ++j) {
			Ray cast(point(i - 150.0, j - 150.0, -5), vec(0, 0, 1)); // - 150 to center the image
			std::deque<Intersection> xs = cast.intersect(s);
			if (hit(xs) >= 0) c.writePixel(i, j, Color(0, 1, 0));
		}
	}

	ofstream renderFile;
	renderFile.open("render.ppm");
	renderFile << c.toPPM();
	renderFile.close();

	return 0;
}
