#pragma once
#include "Tuple.h"

class Ray
{
private:
	Tuple origin_;
	Tuple direction_;
public:

	Ray(Tuple, Tuple);
	Ray(Tuple*, Tuple*);
	Tuple origin() const {return origin_;}
	Tuple direction() const { return direction_; }
	Tuple position(double);

};



