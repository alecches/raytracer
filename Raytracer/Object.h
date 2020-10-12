#pragma once
/*
#include "Tuple.h"
#include "Matrix.h"
#include "Material.h"
*/
#include <deque>
// forward decls
#include "Tuple.h";
#include "Matrix.h";
#include "Material.h";
#include "Intersection.h";
#include "Ray.h";
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
	Object(Object* const o) : position_{ o->position() }, transform_{ o->transform() }, mat_{ o->material() } {}
	virtual Object* heapObject() const = 0;

	Tuple position() { return position_; }
	void position(const Tuple& t) { position_ = t; }
	Matrix transform() { return transform_; }
	void transform(const Matrix& m) { transform_ = m; }
	Material material() { return mat_; }
	void material(const Material& m) { mat_ = m; }

	virtual Tuple normalAt(Tuple) const = 0;
	virtual std::deque<Intersection> intersect(const Ray&) = 0;
	virtual ~Object() {}
};

Tuple normalAt(const Tuple& t, Object* const);
std::deque<Intersection> intersect(const Ray&, Object* const);
