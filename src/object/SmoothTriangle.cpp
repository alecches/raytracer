#include "SmoothTriangle.h"
#include "../struct/Util.h"

Tuple SmoothTriangle::normalAt(Tuple objectPoint, const Intersection& i) const {
	return (n2_ * i.u + n3_ * i.v + n1_ * (1.0 - i.u - i.v)).normalize();
}

Bounds SmoothTriangle::boundingBox() const {


	Tuple min = point(doubleMin(p1_.x, p2_.x, p3_.x), doubleMin(p1_.y, p2_.y, p3_.y), doubleMin(p1_.z, p2_.z, p3_.z));
	Tuple max = point(doubleMax(p1_.x, p2_.x, p3_.x), doubleMax(p1_.y, p2_.y, p3_.y), doubleMax(p1_.z, p2_.z, p3_.z));

	return Bounds(min, max);
}


SmoothTriangle::SmoothTriangle(Tuple a, Tuple b, Tuple c, Tuple d, Tuple e, Tuple f) : 
	p1_{ a }, p2_{ b }, p3_{ c }, n1_{ d }, n2_{ e }, n3_{ f } {
	e1_ = p2_ - p1_;
	e2_ = p3_ - p1_;
}

void SmoothTriangle::localIntersect(const Ray& r, std::vector<Intersection>& intx) const {
	Tuple dirCrossE2 = r.direction().cross(e2_);
	double determinant = e1_.dot(dirCrossE2);
	if (doubleEqual(determinant, 0.0)) return;

	double f = 1.0 / determinant;
	Tuple p1ToOrigin = r.origin() - p1_;
	double u = p1ToOrigin.dot(dirCrossE2) * f;
	if (u < 0.0 || u > 1.0) return;

	Tuple originCrossE1 = p1ToOrigin.cross(e1_);
	double v = r.direction().dot(originCrossE1) * f;
	if (v < 0.0 || (u + v) > 1.0) return;

	double t = f * e2_.dot(originCrossE1);

	intx.push_back(intersectionWithUV(t, this, u, v));
}