#pragma once
#include "../object/Object.h"

class Plane: public Object
{
public:
	Plane() : Object() {}
	Plane(const Plane& p) : Object(p) {}
	Object* heapObject() const; 

	Tuple normalAt(Tuple) const;
	void localIntersect(const Ray&, std::vector<Intersection>& intx) const;
};

