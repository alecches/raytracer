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

	ObjParser parser(true); // true means we're using bounding boxes (THE LATEST FEATURE!!!)
	// idea: lets just make bounding boxes a utility function in parser.h in the future

	parser.parse("../../../test/files/teapot.obj");

	for (auto g : parser.boundedGroups()) {
		g.transform(rotationY(PI / 2));
		w.addObject(g);
	}

	PointLight pl(point(-1, 5, 5), Color(1, 1, 1));
	w.addLight(pl);


	Camera c(300, 200, PI / 3);
	c.transform(view(point(0, 2.25, 7), point(0, 1.5, 0), vec(0, 1, 0)));

	Canvas image = renderWithAntialias(c, w);

	ofstream renderFile;
	renderFile.open("../../../images/smoothTest2.ppm");
	renderFile << image.toPPM();
	renderFile.close();

	return 0;
}
