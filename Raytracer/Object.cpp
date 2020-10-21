#include "Object.h"
#include "Ray.h"
#include "Matrix.h"
#include "Intersection.h"

void intersect(const Ray& r, const Object& o, std::deque<Intersection>& intx) {

	Ray rayT = o.transform().inverse() * r;
	o.intersect(rayT, intx);

}

Tuple normalAt(const Tuple& worldSpacePoint, const Object& object) {
	Tuple objectSpacePoint = object.transform().inverse() * worldSpacePoint;
	Tuple objectNormal = object.normalAt(objectSpacePoint);
	Tuple worldNormal = object.transform().inverse().transpose() * objectNormal;
	worldNormal.w = 0;
	return worldNormal.normalize();
}