#pragma once
#include "../struct/Tuple.h"

class Ray
{
private:
	Tuple origin_;
	Tuple direction_;
public:

	Ray() : origin_{ point(0, 0, 0) }, direction_{ vec(0, 0, 0) } {}
	Ray(Tuple, Tuple);
	Ray(Tuple*, Tuple*);
	Tuple origin() const {return origin_;}
	Tuple direction() const { return direction_; }
	Tuple position(double);

};



