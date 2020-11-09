#pragma once

//class Matrix; some circular stuff was happening
//#include "../struct/Tuple.h"
//class Matrix;
//Matrix identity();

#include "../object/Object.h"

class Sphere : public Object
{
private:
	
public:

	Sphere(): Object(){}
	Sphere(const Sphere& s) : Object(s) {}

	Tuple normalAt(Tuple p) const;
	void intersect(const Ray&, std::vector<Intersection>&) const;

	Object* heapObject() const;
};

Sphere glassSphere(double);

