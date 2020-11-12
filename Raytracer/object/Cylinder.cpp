#include "Cylinder.h"
#include "../struct/Util.h"

Bounds Cylinder::boundingBox() const {
	return Bounds(point(-1, minimum_, -1), point(1, maximum_, 1));
}


Tuple Cylinder::normalAt(Tuple objectPoint) const {

	double distance = pow(objectPoint.x, 2) + pow(objectPoint.z, 2);
	if (distance < 1 && objectPoint.y >= (maximum_ - Epsilon)) return vec(0, 1, 0);
	if (distance < 1 && objectPoint.y <= (minimum_ + Epsilon)) return vec(0, -1, 0);

	return vec(objectPoint.x, 0, objectPoint.z);
}

void Cylinder::localIntersect(const Ray& r, std::vector<Intersection>& intx) const {
	
	Tuple origin = r.origin();
	Tuple direction = r.direction();

	double a = pow(direction.x, 2) + pow(direction.z, 2);
	if (!doubleEqual(a, 0)) {

		double b = 2 * origin.x * direction.x + 2 * origin.z * direction.z;
		double c = pow(origin.x, 2) + pow(origin.z, 2) - 1;
		double discriminant = pow(b, 2) - 4 * a * c;

		if (discriminant < 0) return;

		double t0 = (-b - sqrt(discriminant)) / (2 * a);
		double t1 = (-b + sqrt(discriminant)) / (2 * a);

		double y0 = origin.y + t0 * direction.y;
		if (y0 > minimum_&& y0 < maximum_) intx.push_back(Intersection(t0, this));
		double y1 = origin.y + t1 * direction.y;
		if (y1 > minimum_&& y1 < maximum_) intx.push_back(Intersection(t1, this));
	}

	intersectCaps(r, intx);

}

bool withinCylinderCap(const Ray& r, double t) {
	double x = r.origin().x + t * r.direction().x;
	double z = r.origin().z + t * r.direction().z;
	return (pow(x, 2) + pow(z, 2)) <= 1;
}

void Cylinder::intersectCaps(const Ray& r, std::vector<Intersection>& intx) const {
	Tuple direction = r.direction();
	if (closed == false) return;
	if (doubleEqual(direction.y, 0)) return;
	Tuple origin = r.origin();

	double tl = (minimum_ - origin.y) / direction.y;
	if (withinCylinderCap(r, tl)) intx.push_back(Intersection(tl, this));

	double tu = (maximum_ - origin.y) / direction.y;
	if (withinCylinderCap(r, tu)) intx.push_back(Intersection(tu, this));
}