#include "Cube.h"
#include <limits>
#include "../struct/Util.h"

double cubeMax(double a, double b, double c) {
	double max = a;
	if (b > max) max = b;
	if (c > max) max = c;
	return max;
}

double cubeMin(double a, double b, double c) {
	double min = a;
	if (b < min) min = b;
	if (c < min) min = c;
	return min;
}

Tuple Cube::normalAt(Tuple objectPoint) const {
	double max = cubeMax(abs(objectPoint.x), abs(objectPoint.y), abs(objectPoint.z));

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

void Cube::intersect(const Ray& r, std::vector<Intersection>& intx) const {

	std::pair<double, double> x = checkAxis(r.origin().x, r.direction().x);
	std::pair<double, double> y = checkAxis(r.origin().y, r.direction().y);
	std::pair<double, double> z = checkAxis(r.origin().z, r.direction().z);

	// get the max of the min's
	double tmin = cubeMax(x.first, y.first, z.first);
	
	// get the min of the max's
	double tmax = cubeMin(x.second, y.second, z.second);

	if (tmin > tmax) return;

	intx.push_back(Intersection(tmin, this));
	intx.push_back(Intersection(tmax, this));

}



