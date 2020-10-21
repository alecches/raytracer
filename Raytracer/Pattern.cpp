#include "Pattern.h"
#include "Object.h"
#include <cmath>



Color Pattern::colorAtObject(const Tuple& point, const Object& object) const {

	Tuple objectSpacePoint = object.transform().inverse() * point;
	Tuple patternSpacePoint = transform_.inverse() * objectSpacePoint;
	return colorAt(patternSpacePoint);

}

Color stripePattern::colorAt(const Tuple& point) const {
	if (static_cast<int>(floor(point.x)) % 2 == 0) return a_;
	else return b_;
}

Color gradientPattern::colorAt(const Tuple& point) const {
	return a_ + (b_ - a_) * (point.x - floor(point.x));
}

Color ringPattern::colorAt(const Tuple& point) const {
	if (static_cast<int>(floor(sqrt(pow(point.x, 2) + pow(point.z, 2)))) % 2 == 0) return a_;
	else return b_;
}

Color checkerPattern::colorAt(const Tuple& point)const {
	if (static_cast<int>(floor(point.x) + floor(point.y) + floor(point.z)) % 2 == 0) return a_;
	else return b_;
}
