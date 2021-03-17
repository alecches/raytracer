#include <fstream>
#include <iostream>
#include "object/Sphere.h"
#include "object/Plane.h"
#include "object/Cube.h"
#include "world/World.h"
#include "render/Camera.h"
#include "struct/Util.h"
#include "light/PointLight.h"
#include "render/Multithreaded.h"
#include <chrono>


using namespace std;


int main() {

	World w;
	
	Sphere s;
	s.transform(scale(1, 1, 1)*translation(1, 1, 0));
	Material m;
	m.color(Color(0, 0, 1));
	m.reflective(0.9);
	s.material(m);

	Cube cube1;
	cube1.transform(rotationY(PI / 4) * translation(-2, 1, -2));
	m.color(Color(1, 0, 0));
	m.transparency(0.3);
	cube1.material(m);

	Plane p;
	checkerPattern checkers(Color(0,0,0), Color(1, 1, 1));
	checkers.transform(scale(0.1, 0.1, 0.1));
	Material m2;
	m2.pattern(checkers);
	p.material(m2);
	p.transform(scale(10, 1, 10));

	PointLight pl(point(-1, 5, 5), Color(1, 1, 1));
	w.addLight(pl);
	w.addObject(s);
	w.addObject(p);
	w.addObject(cube1);


	Camera c(300, 200, PI / 3);
	c.transform(view(point(0, 2.25, 7), point(0, 1.5, 0), vec(0, 1, 0)));

	auto t0 = std::chrono::high_resolution_clock::now();
	Canvas2 image1 = renderMultithreaded(c, w);
	auto t1 = std::chrono::high_resolution_clock::now();
	cout << "Multithreaded render: ";
	cout << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << "msec" << endl;

	ofstream renderFile1;
	renderFile1.open("../../../images/image1.ppm");
	renderFile1 << image1.toPPM();
	renderFile1.close();

	auto t2 = std::chrono::high_resolution_clock::now();
	Canvas image2 = render(c, w);
	auto t3 = std::chrono::high_resolution_clock::now();
	cout << "Standard render: ";
	cout << std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2).count() << "msec" << endl;

	ofstream renderFile2;
	renderFile2.open("../../../images/image2.ppm");
	renderFile2 << image2.toPPM();
	renderFile2.close();

	return 0;
}
