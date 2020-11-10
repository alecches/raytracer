#include <fstream>
#include <iostream>
#include "object/Sphere.h"
#include "object/Plane.h"
#include "object/Cube.h"
#include "object/Cone.h"
#include "object/Cylinder.h"
#include "world/World.h"
#include "render/Camera.h"
#include "struct/Matrix.h"
#include "struct/Util.h"
#include "light/PointLight.h"


using namespace std;


int main() {

	World w;

	Cone cone;
	cone.closed = true;
	cone.minimum(-1);
	cone.maximum(0);
	Material mCone;
	mCone.color(Color(0.9, 0.9, 0.4));
	mCone.reflective(0.9);
	cone.material(mCone);
	cone.transform(translation(0, 1.2, 0)*rotationX(PI));

	Cylinder cyl;
	cyl.closed = true;
	cyl.maximum(1);
	cyl.minimum(0);
	cyl.material(mCone);
	cyl.transform(translation(0,0.5,1)*rotationX(PI/6));

	Plane floor;
	Material floorMat;
	checkerPattern checkers(Color(0, 0, 0), Color(1, 1, 1));
	floorMat.pattern(checkers);
	floor.material(floorMat);

	PointLight l(point(-8, 8, -8), Color(1, 1, 1));
	w.addLight(l);
	//w.addObject(s);
	w.addObject(floor);
	w.addObject(cone);

	Camera c(600, 300, PI / 3);
	c.transform(view(point(0, 1.5, -5), point(0, 1, 0), vec(0, 1, 0)));

	Canvas image = render(c, w);

	ofstream renderFile;
	renderFile.open("render.ppm");
	renderFile << image.toPPM();
	renderFile.close();

	return 0;
}
