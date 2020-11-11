#pragma once

#include "../object/Object.h"

class Cube : public Object
{
private:

public:

	Cube() : Object() {}
	Cube(const Cube& s) : Object(s) {}

	Tuple normalAt(Tuple p) const;
	void localIntersect(const Ray&, std::vector<Intersection>&) const;

	Object* heapObject() const { return new Cube(*this); }
};

std::pair<double, double> checkAxis(double, double);




