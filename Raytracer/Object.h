#pragma once
/*
#include "Tuple.h"
#include "Matrix.h"
#include "Material.h"
*/
#include <deque>
// forward decls
#include "Tuple.h"
#include "Matrix.h"
#include "Material.h"
#include "Intersection.h"
#include "Ray.h"
//class Intersection;
//class Ray;

// interface for objs (abstract class)
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
	void material(Material& m) { mat_ = m; } // the Material operator= implements Copy & Swap to avoid exceptions that took hours to figure out...

	virtual Tuple normalAt(Tuple) const = 0;
	virtual void intersect(const Ray&, std::deque<Intersection>&) const = 0;
	virtual ~Object() {}
};

Tuple normalAt(const Tuple&, const Object&);
void intersect(std::deque<Intersection>&, const Ray&, const Object& const);
