#include "Triangle.h"
#include "../struct/Util.h"

Bounds Triangle::boundingBox() const {
	Tuple min = point(doubleMin(p1_.x, p2_.x, p3_.x), doubleMin(p1_.y, p2_.y, p3_.y), doubleMin(p1_.z,p2_.z,p3_.z));
	Tuple max = point(doubleMax(p1_.x, p2_.x, p3_.x), doubleMax(p1_.y, p2_.y, p3_.y), doubleMax(p1_.z,p2_.z,p3_.z));

	return Bounds(min, max);
}


Triangle::Triangle(Tuple a, Tuple b, Tuple c) : p1_{ a }, p2_{ b }, p3_{ c } {
	e1_ = p2_ - p1_;
	e2_ = p3_ - p1_;
	normal_ = e2_.cross(e1_).normalize();
}

void Triangle::localIntersect(const Ray& r, std::vector<Intersection>& intx) const {
	Tuple dirCrossE2 = r.direction().cross(e2_);
	double determinant = e1_.dot(dirCrossE2);
	if (doubleEqual(determinant, 0)) return;

	double f = 1 / determinant;
	Tuple p1ToOrigin = r.origin() - p1_;
	double u = p1ToOrigin.dot(dirCrossE2) * f;
	if (u < 0 || u > 1) return;

	Tuple originCrossE1 = p1ToOrigin.cross(e1_);
	double v = f * r.direction().dot(originCrossE1);
	if (v < 0 || (u + v) > 1) return;

	double t = f * e2_.dot(originCrossE1);

	intx.push_back(Intersection(t, this));
}