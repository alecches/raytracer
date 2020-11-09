#include <fstream>
#include <iostream>
#include "object/Sphere.h"
#include "object/Plane.h"
#include "world/World.h"
#include "render/Camera.h"
#include "struct/Matrix.h"
#include "struct/Util.h"
#include "light/PointLight.h"


using namespace std;


int main() {

	World w;

	Sphere s;
	s.transform(translation(0, 1, 1));
	Material sMat;
	sMat.color(Color(0, 0, 0.76));
	sMat.reflective(0.9);
	sMat.transparency(0.6);
	s.material(sMat);

	Plane floor;
	Material floorMat;
	checkerPattern checkers(Color(0, 0, 0), Color(1, 1, 1));
	floorMat.pattern(checkers);
	floor.material(floorMat);

	PointLight l(point(-10, 10, -10), Color(1, 1, 1));
	w.addLight(l);
	w.addObject(s);
	w.addObject(floor);

	Camera c(300, 150, PI / 3);
	c.transform(view(point(0, 1.5, -5), point(0, 1, 0), vec(0, 1, 0)));

	Canvas image = render(c, w);

	ofstream renderFile;
	renderFile.open("render.ppm");
	renderFile << image.toPPM();
	renderFile.close();

	return 0;
}
