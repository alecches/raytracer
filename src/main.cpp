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

	ObjParser parser;
	parser.parse("../RaytracerTest/files/teapotSmooth.obj");
	Object* group = &(parser.groups()[1].second);
	group->transform(rotationX(-PI/2));
	w.addObject(*group);
	PointLight pl(point(-7, 10, 2), Color(1, 1, 1));
	w.addLight(pl);


	// populate scene

	Camera c(200, 100, PI / 3);
	c.transform(view(point(2, 3, -25), point(0, 2, 0), vec(0, 1, 0)));
	//c.transform(view(point(2, 5, -15), point(0, 3, 0), vec(0, 1, 0)));

	Canvas image = render(c, w);

	ofstream renderFile;
	renderFile.open("../images/example-2.ppm");
	renderFile << image.toPPM();
	renderFile.close();

	return 0;
}
