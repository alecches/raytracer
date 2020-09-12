#pragma once
//#include "Sphere.h"
#include <deque>
class Sphere; // a forward-declare

struct Intersection
{
	double t;
	const Sphere* object;

	Intersection(const double, const Sphere&);
	bool operator==(const Intersection&);

};

int hit(const std::deque<Intersection>&);

