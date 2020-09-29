#pragma once
//#include "Sphere.h"
#include <deque>
#include "Tuple.h";
class Ray;
class Object; // a forward-declare

struct Intersection
{
	double t;
	Object* object;

	Intersection(const double, Object* const);
	bool operator==(const Intersection&);

};

struct IntersectInfo {
	double t;
	Object* object;
	Tuple point;
	Tuple eyev;
	Tuple normalv;
	bool inside;

	IntersectInfo(Intersection, Ray);
};

int hit(const std::deque<Intersection>&);
//IntersectInfo prepareIntersection(Intersection, Ray);
