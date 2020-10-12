#include "Object.h"
#include "Ray.h"
#include "Matrix.h"
#include "Intersection.h"

std::deque<Intersection> intersect(const Ray& r, Object* const o) {

	Ray rayT = (*o).transform().inverse() * r;
	return o->intersect(rayT);

}

Tuple normalAt(const Tuple& worldSpacePoint, Object* const object) {
	Tuple objectSpacePoint = object->transform().inverse() * worldSpacePoint;
	Tuple objectNormal = object->normalAt(objectSpacePoint);
	Tuple worldNormal = object->transform().inverse().transpose() * objectNormal;
	worldNormal.w = 0;
	return worldNormal.normalize();
}