#include <fstream>
#include <iostream>
#include "Sphere.h"
#include "Plane.h"
#include "World.h"
#include "Camera.h"
#include "Util.h"
#include "PointLight.h"
#include "Matrix.h"

using namespace std;


int main() {

	World w;

	Sphere s1;
	s1.transform(translation(-0.5, 1, 0.5));
	Material m1;
	m1.color(Color(0.1, 1, 0.5));
	m1.diffuse(0.7);
	m1.specular(0.3);
	stripePattern stripes(Color(1, 1, 0), Color(1, 0, 1));
	stripes.transform(rotationX(PI / 3)*rotationY(PI)*scale(0.1,0.1,0.1));
	m1.pattern(stripes);
	s1.material(m1);
	

	
	Sphere s2;
	s2.transform(translation(1.5, 0.5, -0.5)*scale(0.5, 0.5, 0.5));
	Material m2;
	m2.color(Color(0.5, 1, 0.1));
	m2.diffuse(0.7);
	m2.specular(0.3);
	s2.material(m2);

	Sphere s3;
	s3.transform(translation(-1.5, 0.33, -0.75)*scale(0.33, 0.33, 0.33));
	Material m3;
	m3.color(Color(1, 0.8, 0.1));
	m3.diffuse(0.7);
	m3.specular(0.3);
	s3.material(m3);

	Plane p;
	
	checkerPattern checkers(Color(0, 0, 0), Color(1, 1, 1));
	m3.pattern(checkers);
	m3.color(Color(0, 0, 0));
	p.material(m3);
	

	w.addObject(s1);
	w.addObject(s2);
	w.addObject(s3);
	w.addObject(p);
	PointLight l(point(-10, 10, -10), Color(1, 1, 1));
	w.addLight(l);

	Camera c(300, 150, PI / 3);
	c.transform(view(point(0, 1.5, -5), point(0, 1, 0), vec(0, 1, 0)));

	Canvas image = render(c, w);

	ofstream renderFile;
	renderFile.open("render.ppm");
	renderFile << image.toPPM();
	renderFile.close();

	return 0;
}
