#pragma once
#include "Object.h"

class Triangle : public Object
{
private:
	Tuple p1_, p2_, p3_;
	Tuple e1_, e2_, normal_;
public:

	Triangle(Tuple a, Tuple b, Tuple c);
	Triangle() : Triangle(point(0, 0, 0), point(0, 0, 0), point(0, 0, 0)) {}
	//Triangle(const Triangle&); // default should work

	Tuple p1() const { return p1_; }
	Tuple p2() const { return p2_; }
	Tuple p3() const { return p3_; }
	Tuple e1() const { return e1_; }
	Tuple e2() const { return e2_; }
	Tuple normal() const { return normal_; }

	Bounds boundingBox() const;
	Object* heapObject() const { return new Triangle(*this);}
	Tuple normalAt(Tuple, const Intersection&) const { return normal_; }
	void localIntersect(const Ray&, std::vector<Intersection>&) const;

};

