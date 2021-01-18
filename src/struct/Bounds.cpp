#include "Bounds.h"
#include <vector>
#include <limits>
#include "../struct/Util.h"

std::pair<double, double> checkBoxAxis(double min, double max, double origin, double direction) {
	double tminNumerator = min - origin;
	double tmaxNumerator = max - origin;
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

bool Bounds::intersect(const Ray& r) const {
	std::pair<double, double> x = checkBoxAxis(min.x, max.x, r.origin().x, r.direction().x);
	std::pair<double, double> y = checkBoxAxis(min.y, max.y, r.origin().y, r.direction().y);
	std::pair<double, double> z = checkBoxAxis(min.z, max.z, r.origin().z, r.direction().z);

	// get the max of the min's
	double tmin = doubleMax(x.first, y.first, z.first);

	// get the min of the max's
	double tmax = doubleMin(x.second, y.second, z.second);

	if (tmin > tmax) return false;
	else return true;
}


