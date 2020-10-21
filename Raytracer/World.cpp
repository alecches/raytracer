#include "World.h"
#include "PointLight.h"
#include "Sphere.h"
#include "Tuple.h"
#include <algorithm>
#include <vector>

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

	const std::list<Light*>& lights = w.lights();

	for (auto l : lights) {
		Tuple pointToLight = l->position() - point;
		double distance = pointToLight.magnitude();
		Tuple direction = pointToLight.normalize();

		Ray r(point, direction);
		std::deque<Intersection> intx;
		intersect(r, w, intx);
		int h = hit(intx);
		if (h < 0);
		else if (intx[h].t < distance) return true;
	}

	return false;
}

bool compareT(Intersection a, Intersection b) { return (a.t < b.t); }

void intersect(const Ray& r, const World& w, std::deque<Intersection>& intx) {

	const std::list<Object*>& objs = w.objects();

	for (auto o : objs) intersect(r, *o, intx);

	std::vector<int> ints = { 3, 65, 0, -3 };
	std::vector<Intersection> intxVec = std::vector<Intersection>();
	for (auto i : intx) intxVec.push_back(i);
	std::sort(intxVec.begin(), intxVec.end());
	//std::sort(intx.begin(), intx.end(), [](Intersection a, Intersection b) { return a.t < b.t; });
	std::sort(intx.begin(), intx.end());
	std::sort(ints.begin(), ints.end());

	return;
}

Color shadeHit(const World& w, const IntersectInfo& i) {
	const std::list<Light*>& lights = w.lights();

	Color c(0, 0, 0);
	for (auto l : lights) {
		c = c + lighting(i.object.material(), i.object, *l, i.overPoint, i.eyev, i.normalv, inShadow(w, i.overPoint));
	}

	return c;
}

Color colorAt(const World& w, const Ray& r) {
	std::deque<Intersection> intx;
	intersect(r, w, intx);
	int i = hit(intx);
	if (i < 0) return Color(0, 0, 0);
	IntersectInfo iInf(intx[i], r);
	return shadeHit(w, iInf);
}
