#pragma once
#include "../object/Object.h"
#include <list>

class Group : public Object
{

private:
	//std::list<const Object*> objs_;
	std::vector<Object*> children_; // TODO : refactor to use std::pointers to better handle memory...
	Bounds box_;

public:
	Group() :  children_ { std::vector<Object*>() }, box_{ Bounds() }, Object() {}
	Group(const Group&);
	Object* heapObject() const;

	const std::vector<Object*>& children() const { return children_; }
	void addChild(const Object& o);

	Bounds boundingBox() const;
	Tuple normalAt(Tuple, const Intersection&) const;
	void localIntersect(const Ray&, std::vector<Intersection>& intx) const;
	~Group();
};



