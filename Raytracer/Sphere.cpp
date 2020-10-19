#include "Sphere.h"
/*
Sphere::Sphere() {
	transform_ = identity();
	center_ = Tuple(0, 0, 0, 1);
}*/

Tuple Sphere::normalAt(Tuple objectPoint) const {
	//Tuple objectP = transform_.inverse() * worldP;
	//Tuple objectNormal = objectP - Tuple(0, 0, 0, 1);
	//Tuple worldNormal = transform_.inverse().transpose() * objectNormal;
	//worldNormal.w = 0;
	return objectPoint - Tuple(0, 0, 0, 1);
}

Object* Sphere::heapObject() const {
	return new Sphere(*this);
}

void Sphere::intersect(const Ray& rayT, std::deque<Intersection>& intx) const {
	Tuple origin = rayT.origin();
	Tuple dir = rayT.direction();

	Tuple sphereToRay = origin - Tuple(0, 0, 0, 1); // only have one shape... sphere at world origin
	double a = dir.dot(dir);
	double b = 2 * dir.dot(sphereToRay);
	double c = sphereToRay.dot(sphereToRay) - 1;

	double discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant < 0) return;

	intx.push_front(Intersection((-b + sqrt(discriminant)) / (2.0 * a), *this));
	intx.push_front(Intersection((-b - sqrt(discriminant)) / (2.0 * a), *this));

	return;
}