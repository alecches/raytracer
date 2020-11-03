#pragma once
#include <deque>
#include "../struct/Tuple.h"
#include "../world/Ray.h"
class Object;

struct Intersection
{
	double t;
	const Object& object;

	Intersection(double d, const Object& o) : t{ d }, object{ o } {}
	bool operator==(const Intersection&) const;
	Intersection operator=(const Intersection&);
	//bool operator<(const Intersection&) const;

	~Intersection() {}
};

bool operator<(const Intersection&, const Intersection&);

struct IntersectInfo {
	double t;
	const Object& object;
	Tuple point;
	Tuple overPoint;
	Tuple eyev;
	Tuple normalv;
	Tuple reflectv;
	bool inside;

	IntersectInfo(Intersection, Ray);
	~IntersectInfo();
};

int hit(const std::deque<Intersection>&);
//IntersectInfo prepareIntersection(Intersection, Ray);
