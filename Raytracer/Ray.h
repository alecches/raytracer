#pragma once
#include "Tuple.h"
#include "Intersection.h"
#include "World.h"


class Ray
{
private:
	Tuple origin_;
	Tuple direction_;
public:

	//Ray(const Tuple&, const Tuple&); // would pass refs, not making copies
	Ray(Tuple, Tuple);
	Ray(Tuple*, Tuple*);
	Tuple origin() const {return origin_;}
	Tuple direction() const { return direction_; }
	//void origin(Tuple o) { origin_ = std::move(o); } //we dont want setters.. yet
	Tuple position(double);

	std::deque<Intersection> intersect(Object* const) const; // to be deprecated eventually? only works for spheres
	std::deque<Intersection> intersect(const World&) const;

};

