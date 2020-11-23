#include <fstream>
#include <iostream>
#include "object/Sphere.h"
#include "object/Plane.h"
#include "object/Cube.h"
#include "object/Cone.h"
#include "object/Cylinder.h"
#include "object/Group.h"
#include "object/CSG.h"
#include "world/World.h"
#include "render/Camera.h"
#include "struct/Matrix.h"
#include "struct/Util.h"
#include "light/PointLight.h"
#include "io/ObjParser.h"


using namespace std;


int main() {

	World w;

	// set up the room
	Cube room;
	room.transform(translation(0, 5, 0)*scale(6, 6, 6));
	checkerPattern cp(Color(0, 0, 0), Color(1, 1, 1));
	cp.transform(scale(0.5, 0.5, 0.5));
	Material m0;
	m0.pattern(cp);
	room.material(m0);

	// set up the sphere
	Material m1;
	m1.color(Color(0.8, 0.5, 0));
	m1.reflective(0.7);
	Material m2;
	m2.color(Color(0, 0.5, 0.9));
	Sphere s;
	s.material(m1);

	// set up the cylinder to subtract from the sphere
	Cylinder cu;
	cu.transform(scale(0.5, 0.5, 0.5));
	cu.material(m2);
	CSG shape(operation::csgDifference, s, cu);
	shape.transform(rotationZ(PI / 2) * rotationX(PI / 3));
	PointLight p(point(-5, 5, -5), Color(1, 1, 1));

	// populate scene
	w.addObject(shape);
	w.addObject(room);
	w.addLight(p);

	Camera c(900, 450, PI / 3);
	c.transform(view(point(1.4, 2, -5), point(0, 0, 0), vec(0, 1, 0)));

	Canvas image = render(c, w);

	ofstream renderFile;
	renderFile.open("../images/example-1.ppm");
	renderFile << image.toPPM();
	renderFile.close();

	return 0;
}
