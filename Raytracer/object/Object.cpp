#include "../object/Object.h"
#include "../world/Ray.h"
#include "../struct/Matrix.h"
#include "../struct/Intersection.h"

void intersect(const Ray& r, const Object& o, std::vector<Intersection>& intx) {

	Ray rayT = o.transform().inverse() * r;
	o.localIntersect(rayT, intx);

}

Tuple normalAt(const Tuple& worldSpacePoint, const Object& object, const Intersection& i) {
	//Tuple objectSpacePoint = object.transform().inverse() * worldSpacePoint;
	Tuple objectSpacePoint = worldToObject(worldSpacePoint, object);
	Tuple objectNormal = object.normalAt(objectSpacePoint, i);
	//Tuple worldNormal = object.transform().inverse().transpose() * objectNormal;
	Tuple worldNormal = normalToWorld(objectNormal, object);
	//worldNormal.w = 0;
	//return worldNormal.normalize();
	return worldNormal;
}

Tuple worldToObject(Tuple point, const Object& o) {
	if (o.parent() != nullptr) point = worldToObject(point, *o.parent());
	return o.transform().inverse() * point;
}

Tuple normalToWorld(Tuple norm, const Object& o) {
	norm = o.transform().inverse().transpose() * norm;
	norm.w = 0;
	norm = norm.normalize();

	if (o.parent() != nullptr) {
		norm = normalToWorld(norm, *o.parent());
	}

	return norm;
}