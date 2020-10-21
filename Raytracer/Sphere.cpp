#include "Sphere.h"

Tuple Sphere::normalAt(Tuple objectPoint) const {
	return objectPoint - Tuple(0, 0, 0, 1);
}

Object* Sphere::heapObject() const {
	return new Sphere(*this);
}

void Sphere::intersect(const Ray& rayT, std::deque<Intersection>& intx) const {

	Tuple origin = rayT.origin();
	Tuple dir = rayT.direction();

	Tuple sphereToRay = origin - Tuple(0, 0, 0, 1);
	double a = dir.dot(dir);
	double b = 2 * dir.dot(sphereToRay);
	double c = sphereToRay.dot(sphereToRay) - 1;

	double discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant < 0) return;

	intx.push_front(Intersection((-b + sqrt(discriminant)) / (2.0 * a), *this));
	intx.push_front(Intersection((-b - sqrt(discriminant)) / (2.0 * a), *this));

	return;
}