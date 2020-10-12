#include "Plane.h"
#include "Util.h"

Tuple Plane::normalAt(Tuple objectPoint) const {
	return vec(0,1,0);
}

Object* Plane::heapObject() const {
	return new Plane(*this);
}

std::deque<Intersection> Plane::intersect(const Ray& rayT) {

	Tuple origin = rayT.origin();
	Tuple dir = rayT.direction();

	std::deque<Intersection> intersections;
	if (abs(dir.y) < Epsilon) return intersections;
	
	intersections.push_front(Intersection((-origin.y)/dir.y, this));

	return intersections;
}