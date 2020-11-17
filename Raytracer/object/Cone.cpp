#include "Cone.h"
#include "../struct/Util.h"

Bounds Cone::boundingBox() const {
	return Bounds(point(-1, minimum_, -1), point(1, maximum_, 1));
}

Tuple Cone::normalAt(Tuple objectPoint, const Intersection& i) const {

	double distance = pow(objectPoint.x, 2) + pow(objectPoint.z, 2);
	if (distance < objectPoint.y && objectPoint.y >= (maximum_ - Epsilon)) return vec(0, 1, 0);
	if (distance < objectPoint.y && objectPoint.y <= (minimum_ + Epsilon)) return vec(0, -1, 0);
	
	double y = sqrt(pow(objectPoint.x, 2) + pow(objectPoint.z, 2));
	if (objectPoint.y > 0) y = -y;
	return vec(objectPoint.x, y, objectPoint.z);
}

void Cone::localIntersect(const Ray& r, std::vector<Intersection>& intx) const {

	Tuple origin = r.origin();
	Tuple direction = r.direction();

	double a = pow(direction.x, 2) - pow(direction.y, 2) + pow(direction.z, 2);
	double b = 2 * origin.x * direction.x - 2*origin.y*direction.y + 2 * origin.z * direction.z;
	double c = pow(origin.x, 2) - pow(origin.y, 2) + pow(origin.z, 2);

	if (doubleEqual(a, 0)) {
		if (!doubleEqual(b, 0)) {
			double t = -c / (2 * b);
			double y = origin.y + t * direction.y;
			if (y > minimum_ && y < maximum_) intx.push_back(Intersection(t, this));
		}
	}
	else{

		double discriminant = pow(b, 2) - 4 * a * c;

		if (discriminant < 0) return;

		double t0 = (-b - sqrt(discriminant)) / (2 * a);
		double t1 = (-b + sqrt(discriminant)) / (2 * a);

		double y0 = origin.y + t0 * direction.y;
		if (y0 > minimum_ && y0 < maximum_) intx.push_back(Intersection(t0, this));
		double y1 = origin.y + t1 * direction.y;
		if (y1 > minimum_ && y1 < maximum_) intx.push_back(Intersection(t1, this));
	}

	intersectCaps(r, intx);

}


bool withinConeCap(const Ray& r, double t, double y) {
	double x = r.origin().x + t * r.direction().x;
	double z = r.origin().z + t * r.direction().z;
	return (pow(x, 2) + pow(z, 2)) <= y;
}

void Cone::intersectCaps(const Ray& r, std::vector<Intersection>& intx) const {
	Tuple direction = r.direction();
	if (closed == false) return;
	if (doubleEqual(direction.y, 0)) return;
	Tuple origin = r.origin();

	double tl = (minimum_ - origin.y) / direction.y;
	if (withinConeCap(r, tl, abs(minimum_))) intx.push_back(Intersection(tl, this));

	double tu = (maximum_ - origin.y) / direction.y;
	if (withinConeCap(r, tu, abs(maximum_))) intx.push_back(Intersection(tu, this));
}