#include "CSG.h"
#include <algorithm>

bool CSG::includes(const Object* o) const { 
	return left_->includes(o) || right_->includes(o);
}

CSG::CSG(operation op, Object& left, Object& right) : op_{ op }, box_{ Bounds() }, Object() {
	left.parent(this);
	right.parent(this);
	left_ = left.heapObject();
	right_ = right.heapObject();
}

Bounds CSG::boundingBox() const {
	return Bounds();

}

Tuple CSG::normalAt(Tuple objectPoint, const Intersection& i) const {
	return Tuple();
}

void CSG::localIntersect(const Ray& r, std::vector<Intersection>& intx) const {

	std::vector<Intersection> leftAndRightx;

	intersect(r, *left_, leftAndRightx);
	intersect(r, *right_, leftAndRightx);

	std::sort(leftAndRightx.begin(), leftAndRightx.end(), [](Intersection a, Intersection b) { return a.t < b.t; });

	std::vector<Intersection> allowed = filterIntersections(leftAndRightx);
	for (auto i : allowed) {
		intx.push_back(i);
	}

}

std::vector<Intersection> CSG::filterIntersections(const std::vector<Intersection>& intx) const {

	bool inl = false;
	bool inr = false;

	std::vector<Intersection> result;

	for (auto i : intx) {
		bool lhit = left_->includes(i.object);

		if (intersectionAllowed(op_, lhit, inl, inr)) {
			result.push_back(i);
		}

		if (lhit) {
			inl = !inl;
		}
		else {
			inr = !inr;
		}
	}

	return result;
}

CSG::~CSG() {
	delete left_;
	delete right_;
}

bool intersectionAllowed(operation op, bool lhit, bool inl, bool inr)
{

	if (op == operation::csgUnion) return (lhit && !inr) || (!lhit && !inl);
	else if (op == operation::csgIntersect) return (lhit && inr) || (!lhit && inl);
	else if (op == operation::csgDifference) return (lhit && !inr) || (!lhit && inl);

	return false;
}