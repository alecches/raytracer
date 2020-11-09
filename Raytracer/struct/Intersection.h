#pragma once
#include <vector>
#include "../struct/Tuple.h"
#include "../world/Ray.h"
class Object;

struct Intersection
{
	double t;
	const Object* object;

	Intersection(double d, const Object* o) : t{ d }, object{ o } {}
	bool operator==(const Intersection&) const;
	Intersection& operator=(const Intersection&);
	void swap(Intersection&, Intersection&);
	//bool operator<(const Intersection&) const;

	~Intersection() {}
};

bool operator<(const Intersection&, const Intersection&);

struct IntersectInfo {
	double t, n1, n2;
	const Object& object;
	Tuple point;
	Tuple overPoint, underPoint;
	Tuple eyev;
	Tuple normalv;
	Tuple reflectv;
	bool inside;

	IntersectInfo(Intersection, Ray);
	IntersectInfo(Intersection, Ray, std::vector<Intersection>&);
	~IntersectInfo();
};

int hit(const std::vector<Intersection>&);
double fresnel(const IntersectInfo&);
//IntersectInfo prepareIntersection(Intersection, Ray);
