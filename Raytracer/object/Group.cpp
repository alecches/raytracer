#include "Group.h"
#include <exception>
#include <iostream>

Object* Group::heapObject() const {
	return new Group(*this); // is this enough?
}

void Group::addChild(Object& o) {
	children_.push_back(&o); // maybe only heap an obj in World's call of addObj?
	o.parent(this);
}

Tuple Group::normalAt(Tuple) const {
	std::exception e("logic_error"); 
	std::cerr << "exception thrown: " << e.what() << "\n";
	return vec(0, 0, 0);
}

void Group::localIntersect(const Ray& r, std::vector<Intersection>& intx) const {
	for (auto child : children_) {
		intersect(r, *child, intx);
	}
}

Group::~Group() {
	/*
	for (auto child : children_) {
		delete child;
	}
	*/
}

