#include "../object/Plane.h"
#include "../struct/Util.h"

Tuple Plane::normalAt(Tuple objectPoint) const {
	return vec(0,1,0);
}

Object* Plane::heapObject() const {
	return new Plane(*this);
}

void Plane::intersect(const Ray& rayT, std::deque<Intersection>& intx) const {

	Tuple origin = rayT.origin();
	Tuple dir = rayT.direction();

	if (abs(dir.y) < Epsilon) return;
	
	intx.push_front(Intersection((-origin.y)/dir.y, *this));
	
	return;
}