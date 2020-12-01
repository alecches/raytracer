#pragma once
#include "Tuple.h"
#include "../world/Ray.h"

struct Bounds
{

	Tuple min;
	Tuple max;

	Bounds(Tuple t1, Tuple t2) : min{ t1 }, max{ t2 } {}
	Bounds() : min{ point(0, 0, 0) }, max{ point(0, 0, 0) } {}

	bool intersect(const Ray& r) const;


};

