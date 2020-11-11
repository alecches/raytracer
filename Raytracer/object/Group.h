#pragma once
#include "../object/Object.h"
#include <list>

class Group : public Object
{

private:
	//std::list<const Object*> objs_;
	std::list<Object*> children_;

public:
	Group() : children_{ std::list<Object*>() }, Object() {}
	Group(const Group& p) : children_{ p.children_ }, Object(p) {}
	Object* heapObject() const;

	const std::list<Object*>& children() const { return children_; }
	void addChild(Object& o);

	Tuple normalAt(Tuple) const;
	void localIntersect(const Ray&, std::vector<Intersection>& intx) const;
	~Group();
};

