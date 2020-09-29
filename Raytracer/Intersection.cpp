#include "Intersection.h"
#include "Ray.h" // shouldn't be a circular ref...

Intersection::Intersection(double d, Object* const s) {
	t = d;
	object = s;
}

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

bool Intersection::operator==(const Intersection& i) {
	
	if (t != i.t)return false;
	if (object != i.object) return false;
	return true;
}

IntersectInfo::IntersectInfo(Intersection i, Ray r) {

	t = i.t;
	object = i.object;
	point = Tuple(r.position(t));
	eyev = Tuple(-r.direction());
	normalv = Tuple((*object).normalAt(point));

	if (normalv.dot(eyev) < 0) {
		inside = true;
		normalv = -normalv;
	}
	else inside = false;

}