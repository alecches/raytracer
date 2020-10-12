#pragma once
#include "Object.h"

class Plane: public Object
{
public:
	Plane() : Object() {}
	Plane(const Plane& p) : Object(p) {}
	Object* heapObject() const; 

	Tuple normalAt(Tuple) const;;
	std::deque<Intersection> intersect(const Ray&);
};

