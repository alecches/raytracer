#include "Pattern.h"
#include "Object.h"
#include <cmath>

Color stripePattern::colorAt(const Tuple& point) const {
	if (static_cast<int>(floor(point.x)) % 2 == 0) return a_;
	else return b_;
}

Color stripePattern::colorAtObject(const Tuple& point, const Object& object) const {

	Tuple objectSpacePoint = object.transform().inverse() * point;
	Tuple patternSpacePoint = transform_.inverse() * objectSpacePoint;
	return colorAt(patternSpacePoint);

}

