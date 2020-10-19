#include "Intersection.h"
 // shouldn't be a circular ref...
#include "Util.h"
#include "Object.h"

int hit(const std::deque<Intersection>& i) {

	int h = -1;
	double min = 0;
	for (int x = 0; x < i.size(); ++x) {
		double temp = i[x].t;
		if (h == -1 && temp >= 0) {
			h = x;
			min = temp;
		}
		else if (temp < min && temp >= 0) {
			min = temp;
			h = x;
		}
	}
	return h;

}

Intersection Intersection::operator=(const Intersection& i) {
	return Intersection(i.t, i.object);
}

bool Intersection::operator==(const Intersection& i) {
	
	if (t != i.t)return false;
	if (&object != &(i.object)) return false;
	return true;
}

IntersectInfo::IntersectInfo(Intersection i, Ray r) : t{ i.t }, object{ i.object } {

	point = Tuple(r.position(t));
	eyev = Tuple(-r.direction());
	normalv = Tuple(normalAt(point, object));

	if (normalv.dot(eyev) < 0) {
		inside = true;
		normalv = -normalv;
	}
	else inside = false;

	overPoint = point + normalv * Epsilon;

}

IntersectInfo::~IntersectInfo(){
	
}