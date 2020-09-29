#include "Ray.h"
#include "Sphere.h"
#include <algorithm>

Ray::Ray(Tuple o, Tuple d) {
	origin_ = o;
	direction_ = d;
}

Ray::Ray(Tuple* op, Tuple* dp) {
	origin_ = *op;
	direction_ = *dp;
	// this may make an extra copy...
}

Tuple Ray::position(double t) {
	return origin_ + direction_ * t;
}

std::deque<Intersection> Ray::intersect(Object* const s) const {

	Ray rayT = (*s).transform().inverse() * (*this);
	Tuple origin = rayT.origin();
	Tuple dir = rayT.direction();

	std::deque<Intersection> intersections;
	Tuple sphereToRay = origin - Tuple(0, 0, 0, 1); // only have one shape... sphere at world origin
	double a = dir.dot(dir);
	double b = 2 * dir.dot(sphereToRay);
	double c = sphereToRay.dot(sphereToRay) - 1;

	double discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant < 0) return intersections;

	intersections.push_front(Intersection((-b + sqrt(discriminant)) / (2.0 * a), s));
	intersections.push_front(Intersection((-b - sqrt(discriminant)) / (2.0 * a), s));
	
	return intersections;
}

bool compareT(Intersection a, Intersection b) { return (a.t < b.t); }

std::deque<Intersection> Ray::intersect(const World& w) const {
	std::deque<Intersection> intx = std::deque<Intersection>();
	std::list<Object*> objs = w.objects();

	for (auto o : objs) {
		std::deque<Intersection> intsObj = Ray::intersect(o);
		for (auto i : intsObj) {
			intx.push_front(i); // can do away with these extra moves in the future... just insert obj's into the single deque
		}
	}

	std::sort(intx.begin(), intx.end(), compareT);
	return intx;
}

