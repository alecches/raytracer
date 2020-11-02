#pragma once
#include <deque>
#include "../struct/Tuple.h"
#include "../struct/Matrix.h"
#include "../property/Material.h"
#include "../struct/Intersection.h"
#include "../world/Ray.h"

class Object {
protected:
	Tuple position_;
	Matrix transform_;
	Material mat_;

public:

	Object() : position_{ Tuple(0,0,0,1) }, transform_{ Matrix(identity()) }, mat_{ Material() } {}
	Object(const Object& o) : position_{ o.position() }, transform_{ o.transform() }, mat_{ o.material() } {}
	virtual Object* heapObject() const = 0;

	Tuple position() const { return position_; }
	void position(const Tuple& t) { position_ = t; }
	Matrix transform() const { return transform_; }
	void transform(const Matrix& m) { transform_ = m; }
	const Material& material() const { return mat_; }
	void material(const Material& m) { mat_ = m; } // the Material operator= implements Copy & Swap to avoid exceptions that took hours to figure out...

	virtual Tuple normalAt(Tuple) const = 0;
	virtual void intersect(const Ray&, std::deque<Intersection>&) const = 0;
	virtual ~Object() {}
};

Tuple normalAt(const Tuple&, const Object&);
void intersect(const Ray&, const Object&, std::deque<Intersection>&);
