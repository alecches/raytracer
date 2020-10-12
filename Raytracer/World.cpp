#include "World.h"
#include "PointLight.h"
#include "Sphere.h"
#include "Tuple.h"
#include <algorithm>

World defaultWorld() {

	PointLight l = PointLight(point(-10, 10, -10), Color(1, 1, 1));
	Sphere s1 = Sphere();
	Material m1 = Material();
	m1.color(Color(0.8, 1, 0.6));
	m1.diffuse(0.7);
	m1.specular(0.2);
	s1.material(m1);
	Sphere s2 = Sphere();
	s2.transform(scale(0.5, 0.5, 0.5));

	World w = World();
	w.addLight(l);
	w.addObject(s1);
	w.addObject(s2);

	return w;

}

World::~World() {
	for (auto o : objs_) {
		delete o;
	}

	for (auto l : lights_) {
		delete l;
	}
}

World defaultWorld(Light& l) {

	Sphere s1 = Sphere();
	Material m1 = Material();
	m1.color(Color(0.8, 1, 0.6));
	m1.diffuse(0.7);
	m1.specular(0.2);
	s1.material(m1);
	Sphere s2 = Sphere();
	s2.transform(scale(0.5, 0.5, 0.5));

	World w = World();
	w.addLight(l);
	w.addObject(s1);
	w.addObject(s2);

	return w;

}

bool inShadow(const World& w, const Tuple& point) {

	std::list<Light*> lights = w.lights();

	for (auto l : lights) {
		Tuple pointToLight = l->position() - point;
		double distance = pointToLight.magnitude();
		Tuple direction = pointToLight.normalize();

		Ray r(point, direction);
		std::deque<Intersection> intx = intersect(r, w);
		int h = hit(intx);
		if (h < 0);
		else if (intx[h].t < distance) return true;
	}

	return false;
}

bool compareT(Intersection a, Intersection b) { return (a.t < b.t); }

std::deque<Intersection> intersect(const Ray& r, const World& w) {
	std::deque<Intersection> intx = std::deque<Intersection>();
	std::list<Object*> objs = w.objects();

	for (auto o : objs) {
		std::deque<Intersection> intsObj = intersect(r, o);
		for (auto i : intsObj) {
			intx.push_front(i); // can do away with these extra moves in the future... just insert obj's into the single deque
		}
	}

	std::sort(intx.begin(), intx.end(), compareT);
	return intx;
}

Color shadeHit(const World& w, const IntersectInfo& i) {
	std::list<Light*> lights = w.lights();

	Color c(0, 0, 0);
	for (auto l : lights) {
		c = c + lighting(i.object->material(), *l, i.point, i.eyev, i.normalv, inShadow(w, i.overPoint)); // for now, nothing is in shadow
	}

	return c;
}

Color colorAt(const World& w, const Ray& r) {
	std::deque<Intersection> intx = intersect(r, w);
	int i = hit(intx);
	if (i < 0) return Color(0, 0, 0);
	IntersectInfo iInf(intx[i], r);
	return shadeHit(w, iInf);
}
