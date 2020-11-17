#include "Cube.h"
#include <limits>
#include "../struct/Util.h"

Bounds Cube::boundingBox() const {
	return Bounds(point(-1, -1, -1), point(1, 1, 1));
}

Tuple Cube::normalAt(Tuple objectPoint, const Intersection& i) const {
	double max = doubleMax(abs(objectPoint.x), abs(objectPoint.y), abs(objectPoint.z));

	if (max == abs(objectPoint.x)) return vec(objectPoint.x, 0, 0);
	if (max == abs(objectPoint.y)) return vec(0, objectPoint.y, 0);
	return vec(0, 0, objectPoint.z);

}

std::pair<double, double> checkAxis(double origin, double direction) {
	double tminNumerator = -1 - origin;
	double tmaxNumerator = 1 - origin;
	double tmin, tmax;

	if (abs(direction) >= Epsilon) {
		tmin = tminNumerator / direction;
		tmax = tmaxNumerator / direction;
	}
	else {
		if (tminNumerator > 0) tmin = std::numeric_limits<double>::infinity();
		else tmin = std::numeric_limits<double>::lowest();
		if (tmaxNumerator > 0) tmax = std::numeric_limits<double>::infinity();
		else tmax = std::numeric_limits<double>::lowest();
	}

	if (tmin > tmax) std::swap(tmin, tmax);

	return std::pair<double, double>(tmin, tmax);
}

void Cube::localIntersect(const Ray& r, std::vector<Intersection>& intx) const {

	std::pair<double, double> x = checkAxis(r.origin().x, r.direction().x);
	std::pair<double, double> y = checkAxis(r.origin().y, r.direction().y);
	std::pair<double, double> z = checkAxis(r.origin().z, r.direction().z);

	// get the max of the min's
	double tmin = doubleMax(x.first, y.first, z.first);
	
	// get the min of the max's
	double tmax = doubleMin(x.second, y.second, z.second);

	if (tmin > tmax) return;

	intx.push_back(Intersection(tmin, this));
	intx.push_back(Intersection(tmax, this));

}



