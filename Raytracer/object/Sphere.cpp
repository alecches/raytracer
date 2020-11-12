#include "../object/Sphere.h"

Bounds Sphere::boundingBox() const {
	return Bounds(point(-1, -1, -1), point(1, 1, 1));
}

Tuple Sphere::normalAt(Tuple objectPoint) const {
	return objectPoint - Tuple(0, 0, 0, 1);
}

Object* Sphere::heapObject() const {
	return new Sphere(*this);
}

void Sphere::localIntersect(const Ray& rayT, std::vector<Intersection>& intx) const {

	Tuple origin = rayT.origin();
	Tuple dir = rayT.direction();

	Tuple sphereToRay = origin - Tuple(0, 0, 0, 1);
	double a = dir.dot(dir);
	double b = 2 * dir.dot(sphereToRay);
	double c = sphereToRay.dot(sphereToRay) - 1;

	double discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant < 0) return;

	intx.push_back(Intersection((-b + sqrt(discriminant)) / (2.0 * a), this));
	intx.push_back(Intersection((-b - sqrt(discriminant)) / (2.0 * a), this));

	return;
}

Sphere glassSphere(double n) {

	Material m;
	m.transparency(1.0);
	m.refractiveIndex(n);
	Sphere s;
	s.material(m);

	return s;
}