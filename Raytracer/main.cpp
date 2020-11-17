#include <fstream>
#include <iostream>
#include "object/Sphere.h"
#include "object/Plane.h"
#include "object/Cube.h"
#include "object/Cone.h"
#include "object/Cylinder.h"
#include "object/Group.h"
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
	parser.parse("../RaytracerTest/files/testCube.txt");
	Group g = parser.objToGroup();
	g.transform(rotationX(PI / 6) * rotationY(PI / 4));
	PointLight l(point(-8, 8, -8), Color(1, 1, 1));
	w.addLight(l);
	w.addObject(g);

	Camera c(600, 300, PI / 3);
	c.transform(view(point(0, 1.5, -5), point(0, 1, 0), vec(0, 1, 0)));

	Canvas image = render(c, w);

	ofstream renderFile;
	renderFile.open("render.ppm");
	renderFile << image.toPPM();
	renderFile.close();

	return 0;
}
