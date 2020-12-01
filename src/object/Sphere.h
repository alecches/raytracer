#pragma once
#include "../object/Object.h"

class Sphere : public Object
{
private:
	
public:

	Sphere(): Object(){}
	Sphere(const Sphere& s) : Object(s) {}

	Bounds boundingBox() const;
	Tuple normalAt(Tuple, const Intersection&) const;
	void localIntersect(const Ray&, std::vector<Intersection>&) const;

	Object* heapObject() const;
};

Sphere glassSphere(double);

