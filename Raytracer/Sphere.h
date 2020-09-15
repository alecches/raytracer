#pragma once

#include "Matrix.h" //// THIS MAKES IT ALL CIRCULAR!
//class Matrix;
//#include "Tuple.h"
//class Matrix;
//Matrix identity();

class Sphere
{
private:
	Tuple center_;
	Matrix transform_;
public:
	Sphere():center_{ Tuple(0,0,0,1) }, transform_{ identity() } {};
	Matrix transform() const { return transform_; }
	void transform(Matrix m) { transform_ = std::move(m); }
};


