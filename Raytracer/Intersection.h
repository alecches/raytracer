#pragma once
//#include "Sphere.h"
#include <deque>
#include "Tuple.h"
#include "Ray.h"
//#include "Object.h"
class Object; // a forward-declare

struct Intersection
{
	const double t;
	const Object& object;

	Intersection(const double d, const Object& o) : t{ d }, object{ o } {}
	bool operator==(const Intersection&);
	Intersection operator=(const Intersection&);

	~Intersection() {}
};

struct IntersectInfo {
	double t;
	const Object& object;
	Tuple point;
	Tuple overPoint;
	Tuple eyev;
	Tuple normalv;
	bool inside;

	IntersectInfo(Intersection, Ray);
	~IntersectInfo();
};

int hit(const std::deque<Intersection>&);
//IntersectInfo prepareIntersection(Intersection, Ray);
