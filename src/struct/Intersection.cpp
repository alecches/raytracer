#include "../struct/Intersection.h"
 // shouldn't be a circular ref...
#include "../struct/Util.h"
#include "../object/Object.h"
#include <list>

int hit(const std::vector<Intersection>& i) {

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

Intersection intersectionWithUV(double d, const Object* o, double u, double v) {
	Intersection i(d, o);
	i.u = u;
	i.v = v;
	return i;
}

Intersection& Intersection::operator=(const Intersection& i) {
	Intersection iTemp(i.t, i.object);
	swap(*this, iTemp);
	return *this;
}

void Intersection::swap(Intersection& first, Intersection& second) {
	std::swap(first.t, second.t);
	std::swap(first.object, second.object);
}


bool Intersection::operator==(const Intersection& i) const {
	
	if (t != i.t)return false;
	if (&object != &(i.object)) return false;
	return true;
}

/*bool Intersection::operator<(const Intersection& i) const {
	return t < i.t;
}*/

bool operator<(const Intersection& i1, const Intersection& i2) {
	return i1.t < i2.t;
}

IntersectInfo::IntersectInfo(Intersection i, Ray r) : t{ i.t }, object{ *i.object } {

	point = Tuple(r.position(t));
	eyev = Tuple(-r.direction());
	normalv = Tuple(normalAt(point, object, i));
	reflectv = r.direction().reflect(normalv);

	if (normalv.dot(eyev) < 0) { // we are entering this block when we shouldnt with smooth tris (was < )
		inside = true;
		normalv = -normalv;
	}
	else inside = false;

	overPoint = point + normalv * Epsilon;
	underPoint = point - normalv * Epsilon;

	n1 = 1;
	n2 = object.material().refractiveIndex();

}

IntersectInfo::IntersectInfo(Intersection i, Ray r, std::vector<Intersection>& intx) : t{ i.t }, object{ *i.object } {

	point = Tuple(r.position(t));
	eyev = Tuple(-r.direction());
	normalv = Tuple(normalAt(point, object, i));
	reflectv = r.direction().reflect(normalv);

	if (normalv.dot(eyev) < 0) {
		inside = true;
		normalv = -normalv;
	}
	else inside = false;

	overPoint = point + normalv * Epsilon;
	underPoint = point - normalv * Epsilon;

	n1 = 1;
	n2 = object.material().refractiveIndex();

	std::list<const Object*> within;
	for (auto ix : intx) {

		if (ix.t == t) { // we're at the hit
			if (within.size() == 0) n1 = 1;
			else n1 = (*within.back()).material().refractiveIndex();
		}

		std::list<const Object*>::iterator objIt = std::find(within.begin(), within.end(), ix.object);
		if (objIt != within.end()) within.remove(ix.object);		
		else within.push_back(ix.object);

		if (ix.t == t) {
			if (within.size() == 0) n2 = 1;
			else n2 = (*within.back()).material().refractiveIndex();
		}

	}

}

IntersectInfo::~IntersectInfo(){
	
}

double fresnel(const IntersectInfo& iInf) {
	double cosine = iInf.eyev.dot(iInf.normalv);
	double n1 = iInf.n1;
	double n2 = iInf.n2;


	if (n1 > n2) {
		double n = n1 / n2;
		double sin2T = pow(n, 2) * (1 - pow(cosine, 2));
		if (sin2T > 1) return 1;

		double cosT = sqrt(1 - sin2T);
		cosine = cosT;
	}

	double r = pow((n1 - n2) / (n1 + n2), 2);

	return r + (1 - r) * pow(1-cosine, 5);
}

