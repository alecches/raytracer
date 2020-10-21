#pragma once

//class Matrix; some circular stuff was happening
//#include "Tuple.h"
//class Matrix;
//Matrix identity();

#include "Object.h"

class Sphere : public Object
{
private:
	
public:

	Sphere(): Object(){}
	Sphere(const Sphere& s) : Object(s) {}

	Tuple normalAt(Tuple p) const;
	void intersect(const Ray&, std::deque<Intersection>&) const;

	Object* heapObject() const;
};


