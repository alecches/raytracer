#pragma once

//class Matrix; some circular stuff was happening
//#include "Tuple.h"
//class Matrix;
//Matrix identity();

#include "Object.h"

class Sphere : public Object
{
private:
	//Tuple center_;
	//Matrix transform_;
	//Material mat_;
public:

	Sphere(): Object(){}
	Sphere(const Sphere& s) : Object(s) {}
	//Sphere(const Sphere& s) : center_{ s.position() }, transform_{ s.transform() }, mat_{s.material()} {}
	//Matrix transform() const { return transform_; }
	//Material material() const { return mat_; }
	//Tuple position() const { return center_; }
	//void transform(Matrix m) { transform_ =  m; }
	//void material(Material mat) { mat_ = std::move(mat); }
	//void transform(Matrix m) { transform_ = std::move(m); }
	//void material(Material mat) { mat_ = std::move(mat); }
	Tuple normalAt(Tuple p) const;
	void intersect(const Ray&, std::deque<Intersection>&) const;

	Object* heapObject() const;
};


