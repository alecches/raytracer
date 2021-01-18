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

	Sphere s;
	

	PointLight pl(point(0, 0, -6), Color(1, 1, 1));
	w.addLight(pl);
	w.addObject(s);


	Camera c(150, 150, PI / 6);
	//c.transform(view(point(3, 3, -3), point(0, 0, 0), vec(0, 1, 0)));
	c.transform(view(point(0, 0, -5), point(0, 0, 0), vec(0, 1, 0)));
	//c.transform(view(point(2, 5, -15), point(0, 3, 0), vec(0, 1, 0)));

	Canvas image = render(c, w);

	ofstream renderFile;
	renderFile.open("../images/aSphere.ppm");
	renderFile << image.toPPM();
	renderFile.close();

	return 0;
}
