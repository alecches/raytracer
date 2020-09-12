#include "Intersection.h"

Intersection::Intersection(double d, const Sphere& s) {
	t = d;
	object = &s;
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