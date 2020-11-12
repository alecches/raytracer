#pragma once

#include "../object/Object.h"
#include <limits>

class Cone : public Object
{
private:
	double minimum_, maximum_;
	void intersectCaps(const Ray&, std::vector<Intersection>&) const;

public:
	bool closed;

	Cone() : closed{ false }, minimum_{ std::numeric_limits<double>::lowest() }, maximum_{ std::numeric_limits<double>::infinity() }, Object() {}
	Cone(const Cone& s) : closed{ s.closed }, minimum_{ s.minimum() }, maximum_{ s.maximum() }, Object(s) {}

	Bounds boundingBox() const;
	Tuple normalAt(Tuple p) const;
	void localIntersect(const Ray&, std::vector<Intersection>&) const;
	double maximum() const { return maximum_; }
	void maximum(double d) { maximum_ = d; }
	double minimum() const { return minimum_; }
	void minimum(double d) { minimum_ = d; }

	Object* heapObject() const { return new Cone(*this); }
};





