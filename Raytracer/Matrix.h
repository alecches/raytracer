#pragma once
#include "Ray.h"
// sort of a mess, maybe use Eigen in the future?

class Matrix
{
private:
	unsigned row, col;
	double* m;
	struct Comma {
		Matrix& mat;
		int i;
		Comma(Matrix& m, int i) : mat(m), i(i) {}
		Comma operator , (double val) {
			mat.m[i] = val;
			return Comma(mat, i + 1);
		}
	};
	

public:

	Matrix(){}
	Matrix(unsigned, unsigned);
	Comma operator<<(double val) {
		m[0] = val;
		return Comma(*this, 1);
	}
	double& operator()(unsigned, unsigned);
	double operator()(unsigned, unsigned) const;
	bool operator==(const Matrix&);
	Matrix operator*(const Matrix&);
	Tuple operator*(const Tuple&);
	Ray operator*(const Ray&);
	Matrix transpose();
	double determinant();
	Matrix submatrix(unsigned, unsigned);
	double minor(unsigned, unsigned);
	double cofactor(unsigned, unsigned);
	bool isInvertible();
	Matrix inverse();
};

Matrix identity();
Matrix translation(double, double, double);
Matrix scale(double, double, double);
Matrix rotationX(double);
Matrix rotationY(double);
Matrix rotationZ(double);
Matrix shear(double, double, double, double, double, double);


