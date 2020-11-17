#pragma once
#include "Object.h"
class SmoothTriangle :
	public Object
{
private:
	Tuple p1_, p2_, p3_;
	Tuple e1_, e2_, n1_, n2_, n3_;
public:

	SmoothTriangle(Tuple a, Tuple b, Tuple c, Tuple d, Tuple e, Tuple f);
	SmoothTriangle() : SmoothTriangle(point(0, 0, 0), point(0, 0, 0), point(0, 0, 0),
		point(0, 0, 0), point(0, 0, 0), point(0, 0, 0)) {}
	//Triangle(const Triangle&); // default should work

	Tuple p1() const { return p1_; }
	Tuple p2() const { return p2_; }
	Tuple p3() const { return p3_; }
	Tuple n1() const { return n1_; }
	Tuple n2() const { return n2_; }
	Tuple n3() const { return n3_; }
	Tuple e1() const { return e1_; }
	Tuple e2() const { return e2_; }

	Bounds boundingBox() const;
	Object* heapObject() const { return new SmoothTriangle(*this); }
	Tuple normalAt(Tuple, const Intersection&) const;
	void localIntersect(const Ray&, std::vector<Intersection>&) const;
};

