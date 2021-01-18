#include "../world/World.h"
#include "../light/PointLight.h"
#include "../object/Sphere.h"
#include "../struct/Tuple.h"
#include <algorithm>
#include <vector>
#include <cmath>

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

World::World(const World& w) {

	for (auto o : w.objects()) {
		objs_.push_back(o->heapObject());
	}

	for (auto l : w.lights()) {
		lights_.push_back(l->heapLight());
	}
	
}

World& World::operator=(const World& w) {
	World tempWorld(w);
	swap(*this, tempWorld);
	return *this;
}


void World::swap(World& first, World& second) {
	std::swap(first.lights_, second.lights_);
	std::swap(first.objs_, second.objs_);
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
		std::vector<Intersection> intx;
		intersect(r, w, intx);
		int h = hit(intx);
		if (h < 0);
		else if (intx[h].t < distance) return true;
	}

	return false;
}


void intersect(const Ray& r, const World& w, std::vector<Intersection>& intx) {

	const std::list<Object*>& objs = w.objects();

	for (auto o : objs) intersect(r, *o, intx);

	std::sort(intx.begin(), intx.end(), [](const Intersection & a, const Intersection & b) { return a.t < b.t; });

	return;
}

Color shadeHit(const World& w, const IntersectInfo& i, int remainingDepth) {
	const std::list<Light*>& lights = w.lights();

	Color surface(0, 0, 0);
	//if (lights.size() == 0) surface = i.object.material().ambient();
	for (auto l : lights) {
		surface = surface + lighting(i.object.material(), i.object, *l, i.overPoint, i.eyev, i.normalv, inShadow(w, i.overPoint));
	}

	Color reflected = reflectedColor(w, i, remainingDepth);

	Color refracted = refractedColor(w, i, remainingDepth);

	Material m = i.object.material();
	if (m.reflective() > 0 && m.transparency() > 0) {
		double reflectance = fresnel(i);
		return surface + reflected * reflectance + refracted * (1 - reflectance);
	}

	return surface + reflected + refracted;
}

Color colorAt(const World& w, const Ray& r, int remainingDepth) {
	std::vector<Intersection> intx;
	intersect(r, w, intx);
	int i = hit(intx);
	if (i < 0) return Color(0, 0, 0);
	IntersectInfo iInf(intx[i], r, intx);
	return shadeHit(w, iInf, remainingDepth);
}

Color reflectedColor(const World& w, const IntersectInfo& iInf, int remainingDepth) {

	if (remainingDepth < 1) return Color(0, 0, 0);
	if (iInf.object.material().reflective() == 0) return Color(0, 0, 0); // code smell

	Ray reflectedRay(iInf.overPoint, iInf.reflectv);
	Color reflectedColor = colorAt(w, reflectedRay, --remainingDepth);

	return reflectedColor * (iInf.object.material().reflective()); // so many dot operators..

}

Color refractedColor(const World& w, const IntersectInfo& iInf, int remainingDepth) {

	// is the material opaque ? are we at the max depth ?
	if (iInf.object.material().transparency() == 0 || remainingDepth == 0) return Color(0, 0, 0);

	//check for total internal reflection
	double nRatio = iInf.n1 / iInf.n2;
	double cosI = iInf.eyev.dot(iInf.normalv);
	double sin2T = pow(nRatio, 2) * (1 - pow(cosI, 2));
	if (sin2T > 1) return Color(0, 0, 0);

	// create the refracted ray
	double cosT = sqrt(1 - sin2T);
	Tuple dir = iInf.normalv * (nRatio * cosI - cosT) - iInf.eyev * nRatio;
	Ray refractedRay(iInf.underPoint, dir);

	return colorAt(w, refractedRay, --remainingDepth) * iInf.object.material().transparency();
}
