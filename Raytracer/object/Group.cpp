#include "Group.h"
#include <exception>
#include <iostream>

Bounds Group::boundingBox() const {

	Tuple min;
	Tuple max;
	int child = 0;
	for (auto obj : children_) {
		Bounds objBounds = obj->boundingBox();
		//Tuple groupSpaceMin = obj->transform() * objBounds.min;
		Tuple XYZ = objBounds.min;
		//Tuple groupSpaceMax = obj->transform() * objBounds.max;
		Tuple xyz = objBounds.max;

		std::vector<Tuple> points;
		points.push_back(XYZ);
		points.push_back(xyz);
		points.push_back(point(XYZ.x, XYZ.y, xyz.z));
		points.push_back(point(XYZ.x, xyz.y, xyz.z));
		points.push_back(point(XYZ.x, xyz.y, XYZ.z));
		points.push_back(point(xyz.x, xyz.y, XYZ.z));
		points.push_back(point(xyz.x, XYZ.y, xyz.z));
		points.push_back(point(xyz.x, XYZ.y, XYZ.z));

		int i = 0;
		if (child == 0) {
			min = obj->transform() * xyz;
			max = obj->transform() * XYZ;
			i = 2;
		}
		
		for (i; i < 8; i++) {
			points[i] = obj -> transform() * points[i];
			if (points[i].x < min.x) min.x = points[i].x;
			else if (points[i].x > max.x) max.x = points[i].x;
			if (points[i].y < min.y) min.y = points[i].y;
			else if (points[i].y > max.y) max.y = points[i].y;
			if (points[i].z < min.z) min.z = points[i].z;
			else if (points[i].z > max.z) max.z = points[i].z;
		}

		child++;
	}

	return Bounds(min, max);
}

Object* Group::heapObject() const {
	/*
	for (auto obj : children_) {
		obj = (*obj).heapObject();
	}*/
	Group* obj = new Group(*this);
	return obj; // is this enough?
}

void Group::addChild(Object& o) {
	children_.push_back(&o); // maybe only heap an obj in World's call of addObj?
	o.parent(this);
	box_ = boundingBox(); // update the box -- this could be refactored to only test against the new object..
	// set up new bounding box
}

Tuple Group::normalAt(Tuple) const {
	std::exception e("logic_error"); 
	std::cerr << "exception thrown: " << e.what() << "\n";
	return vec(0, 0, 0);
}

void Group::localIntersect(const Ray& r, std::vector<Intersection>& intx) const {
	if (!box_.intersect(r)) return;
	for (auto child : children_) {
		intersect(r, *child, intx);
	}
}

Group::~Group() {
	
}

