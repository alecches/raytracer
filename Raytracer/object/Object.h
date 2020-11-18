#pragma once
#include <vector>
#include "../struct/Tuple.h"
#include "../struct/Matrix.h"
#include "../struct/Bounds.h"
#include "../property/Material.h"
#include "../struct/Intersection.h"
#include "../world/Ray.h"

class Object {
protected:
	Matrix transform_;
	Material mat_;
	const Object* parent_;

public:

	Object() : transform_{ Matrix(identity()) }, mat_{ Material() }, parent_{nullptr} {}
	Object(const Object& o) : transform_{ o.transform() }, mat_{ o.material() }, parent_{ nullptr }  {}
	virtual Object* heapObject() const = 0;

	Matrix transform() const { return transform_; }
	void transform(const Matrix& m) { transform_ = m; }
	const Material& material() const { return mat_; }
	void material(const Material& m) { mat_ = m; } // the Material operator= implements Copy & Swap to avoid exceptions that took hours to figure out...
	const Object* parent() const { return parent_; }
	void parent(const Object* p) { parent_ = p; }

	virtual bool includes(const Object* o) const { return o == this; }
	virtual Bounds boundingBox() const = 0;
	virtual Tuple normalAt(Tuple, const Intersection&) const = 0;
	virtual void localIntersect(const Ray&, std::vector<Intersection>&) const = 0;
	virtual ~Object() {}
};

Tuple normalAt(const Tuple&, const Object&, const Intersection&);
void intersect(const Ray&, const Object&, std::vector<Intersection>&);
Tuple worldToObject(Tuple, const Object&);
Tuple normalToWorld(Tuple, const Object&);
