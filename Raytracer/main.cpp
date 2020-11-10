#include <fstream>
#include <iostream>
#include "object/Sphere.h"
#include "object/Plane.h"
#include "object/Cube.h"
#include "world/World.h"
#include "render/Camera.h"
#include "struct/Matrix.h"
#include "struct/Util.h"
#include "light/PointLight.h"


using namespace std;


int main() {

	World w;

	Cube cube;
	Material mCube;
	mCube.color(Color(0.8, 0.8, 0.4));
	cube.material(mCube);
	cube.transform(scale(10, 10, 10));

	Plane floor;
	Material floorMat;
	checkerPattern checkers(Color(0, 0, 0), Color(1, 1, 1));
	floorMat.pattern(checkers);
	floor.material(floorMat);

	PointLight l(point(-8, 8, -8), Color(1, 1, 1));
	w.addLight(l);
	//w.addObject(s);
	w.addObject(floor);
	w.addObject(cube);

	Camera c(300, 150, PI / 3);
	c.transform(view(point(0, 1.5, -5), point(0, 1, 0), vec(0, 1, 0)));

	Canvas image = render(c, w);

	ofstream renderFile;
	renderFile.open("render.ppm");
	renderFile << image.toPPM();
	renderFile.close();

	return 0;
}
