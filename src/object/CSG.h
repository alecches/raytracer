#pragma once
#include "../object/Object.h"

enum class operation { csgUnion, csgIntersect, csgDifference };

class CSG : public Object
{

private:
	
	operation op_;
	const Object* left_;
	const Object* right_;
	Bounds box_;

public:
	CSG(operation op, Object& left, Object& right);
	CSG(const CSG& c) : op_{ c.op_ },
		left_{ c.left_->heapObject() }, right_{ c.right_->heapObject() }, box_{ Bounds() }, Object(c) {}
	Object* heapObject() const { return new CSG(*this); }


	const Object* left() const { return left_; }
	const Object* right() const { return right_; }
	bool includes(const Object*) const override;
	Bounds boundingBox() const;
	Tuple normalAt(Tuple, const Intersection&) const;
	void localIntersect(const Ray&, std::vector<Intersection>&) const;
	std::vector<Intersection> filterIntersections(const std::vector<Intersection>&) const;
	~CSG();
};

bool intersectionAllowed(operation, bool, bool, bool);