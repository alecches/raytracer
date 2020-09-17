#pragma once

#include "Matrix.h" 
#include "Material.h"
//class Matrix; some circular stuff was happening
//#include "Tuple.h"
//class Matrix;
//Matrix identity();

class Sphere
{
private:
	Tuple center_;
	Matrix transform_;
	Material mat_;
public:
	Sphere() :center_{ Tuple(0,0,0,1) }, transform_{ identity() }, mat_{ Material() } {};
	Matrix transform() const { return transform_; }
	Material material() const { return mat_; }
	void transform(Matrix m) { transform_ = std::move(m); }
	void material(Material mat) { mat_ = std::move(mat); }
	Tuple normalAt(Tuple p);
};


