#pragma once
#include "../object/Object.h"

class Group : public Object
{

private:
	//std::list<const Object*> objs_;
	std::vector<Object*> children_; // TODO : refactor to use std::pointers to better handle memory...
	Bounds box_;
	bool bounded_;

public:
	Group() : children_{ std::vector<Object*>() }, box_{ Bounds() }, bounded_{ false }, Object() {}
	Group(const Group&);
	Object* heapObject() const;

	const std::vector<Object*>& children() const { return children_; }
	void addChild(const Object& o);

	bool includes(const Object*) const override;
	void setBounds() { bounded_ = true; }
	Bounds boundingBox() const;
	void boundingBox(const Bounds& b) { box_ = std::move(b); }
	Tuple normalAt(Tuple, const Intersection&) const;
	void localIntersect(const Ray&, std::vector<Intersection>& intx) const;
	~Group();
};



