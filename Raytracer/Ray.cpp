#include "Ray.h"
#include "Matrix.h"
#include <algorithm>

Ray::Ray(Tuple o, Tuple d) {
	origin_ = o;
	direction_ = d;
}

Ray::Ray(Tuple* op, Tuple* dp) {
	origin_ = *op;
	direction_ = *dp;
	// this may make an extra copy...
}

Tuple Ray::position(double t) {
	return origin_ + direction_ * t;
}




