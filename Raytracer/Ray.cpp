#include "Ray.h"

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

std::deque<Intersection> Ray::intersect(const Sphere& s) {

	std::deque<Intersection> intersections;
	Tuple sphereToRay = origin_ - Tuple(0, 0, 0, 1); // only have one shape... sphere at world origin
	double a = direction_.dot(direction_);
	double b = 2 * direction_.dot(sphereToRay);
	double c = sphereToRay.dot(sphereToRay) - 1;

	double discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant < 0) return intersections;

	intersections.push_front(Intersection((-b + sqrt(discriminant)) / 2 * a, s));
	intersections.push_front(Intersection((-b - sqrt(discriminant)) / 2 * a, s));
	
	return intersections;
}