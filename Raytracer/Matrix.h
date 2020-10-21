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

	Matrix(): row{ 4 }, col{ 4 }, m{ new double[4 * 4] } {}
	Matrix(unsigned w, unsigned l) : row{ w }, col{ l }, m{ new double[w * l] } {}
	Matrix(const Matrix&); // do more research on copy-and-swap and Rule of Three
	void operator=(const Matrix&);
	Comma operator<<(double val) {
		m[0] = val;
		return Comma(*this, 1);
	}
	~Matrix() { delete [] m; }

	double& operator()(unsigned, unsigned);
	double operator()(unsigned, unsigned) const;
	bool operator==(const Matrix&) const;
	Matrix operator*(const Matrix&);
	Tuple operator*(const Tuple&);
	Ray operator*(const Ray&);
	Matrix transpose() const;
	double determinant() const;
	Matrix submatrix(unsigned, unsigned) const;
	double minor(unsigned, unsigned) const;
	double cofactor(unsigned, unsigned) const;
	bool isInvertible() const;
	Matrix inverse() const;
};

Matrix identity();
Matrix translation(double, double, double);
Matrix scale(double, double, double);
Matrix rotationX(double);
Matrix rotationY(double);
Matrix rotationZ(double);
Matrix shear(double, double, double, double, double, double);
Matrix view(Tuple, Tuple, Tuple);


