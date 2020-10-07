#include "World.h"
#include "PointLight.h"
#include "Sphere.h"
#include "TupleFactory.h"

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
		std::deque<Intersection> intx = r.intersect(w);
		int h = hit(intx);
		if (h < 0);
		else if (intx[h].t < distance) return true;
	}

	return false;
}
