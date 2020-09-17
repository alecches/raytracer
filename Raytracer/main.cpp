#include <fstream>
#include <iostream>
#include "Canvas.h"
#include "Color.h"
#include "Matrix.h"
#include "Sphere.h"
#include "TupleFactory.h"
#include "Intersection.h"

using namespace std;


int main() {

	int canvas_pixels = 200;
	Canvas c(canvas_pixels, canvas_pixels);
	Tuple ray_origin = point(0, 0, -5);
	double wall_z = 10;
	double wall_size = 7.0;

	double pixel_size = wall_size / static_cast<double>(canvas_pixels);
	double half_wall = wall_size / 2;

	Sphere s;
	Material m;
	m.color(Color(1, 0.2, 1));
	s.material(m);

	PointLight light(point(-10, 10, -10), Color(1, 1, 1));

	for (int i = 0; i < canvas_pixels; ++i) {

		double world_y = half_wall - pixel_size * i;

		for (int j = 0; j < canvas_pixels; ++j) {

			double world_x = -half_wall + pixel_size * j;
			Tuple target_point = point(world_x, world_y, wall_z);

			Ray cast(ray_origin, (target_point - ray_origin).normalize());
			std::deque<Intersection> xs = cast.intersect(s);

			int h = hit(xs);
			if (h >= 0) {
				Tuple p = cast.position(xs[h].t);
				Sphere obj = *(xs[h].object);
				Tuple normal = obj.normalAt(p);
				Tuple eye = -cast.direction();

				Color col = lighting(obj.material(), light, p, eye, normal);
				
				c.writePixel(j, i, col);
			}
		}
	}

	ofstream renderFile;
	renderFile.open("render.ppm");
	renderFile << c.toPPM();
	renderFile.close();

	return 0;
}
