#include "Sphere.h"
/*
Sphere::Sphere() {
	transform_ = identity();
	center_ = Tuple(0, 0, 0, 1);
}*/

Tuple Sphere::normalAt(Tuple worldP) const {
	Tuple objectP = transform_.inverse() * worldP;
	Tuple objectNormal = objectP - Tuple(0, 0, 0, 1);
	Tuple worldNormal = transform_.inverse().transpose() * objectNormal;
	worldNormal.w = 0;
	return worldNormal.normalize();
}

Object* Sphere::heapObject() const {
	return new Sphere(*this);
}