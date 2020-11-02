#include "../struct/Matrix.h"
#include "../struct/Util.h"
#include <cmath>

/*Matrix::Matrix() {
	row = 4;
	col = 4;
	m = new double[4 * 4];

	(*this) <<
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1;
}*/

Matrix::Matrix(const Matrix& mat) {

	(*this).row = mat.row;
	(*this).col = mat.col;
	(*this).m = new double[row * col];

	for (int i = 0; i < row * col; ++i) {
		(*this).m[i] = mat.m[i];
	}

}

void Matrix::operator=(const Matrix& mat) {

	(*this).row = mat.row;
	(*this).col = mat.col;
	(*this).m = new double[row * col];

	for (int i = 0; i < row * col; ++i) {
		(*this).m[i] = mat.m[i];
	}
	
}

double& Matrix::operator()(unsigned r, unsigned c) {
	return m[r * row + c];
}

double Matrix::operator()(unsigned r, unsigned c) const {
	return m[r*row + c];
}

bool Matrix::operator==(const Matrix& mat2) const {

	if (row != mat2.row || col != mat2.col) {
		return false;
	}

	double a, b;

	for (int x = 0; x < row; x++) {
		for (int y = 0; y < col; y++) {
			a = (*this)(x, y);
			b = mat2(x, y);
			if (!doubleEqual(a,b)) return false;
		}
	}

	return true;
}

Matrix Matrix::operator*(const Matrix& mat2) {
	// only for 4 by 4 matrices
	Matrix product(4, 4);

	for (int iRow = 0; iRow < row; iRow++) {
		for (int iCol = 0; iCol < col; iCol++) {
			product(iRow, iCol) = (*this)(iRow, 0) * mat2(0, iCol) +
									(*this)(iRow, 1) * mat2(1, iCol) +
									(*this)(iRow, 2) * mat2(2, iCol) +
									(*this)(iRow, 3) * mat2(3, iCol);
		}
	}

	return product;
}

Tuple Matrix::operator*(const Tuple& t) {
	Tuple product;
	
	product.x =
		(*this)(0, 0) * t.x +
		(*this)(0, 1) * t.y +
		(*this)(0, 2) * t.z +
		(*this)(0, 3) * t.w;

	product.y =
		(*this)(1, 0) * t.x +
		(*this)(1, 1) * t.y +
		(*this)(1, 2) * t.z +
		(*this)(1, 3) * t.w;

	product.z =
		(*this)(2, 0) * t.x +
		(*this)(2, 1) * t.y +
		(*this)(2, 2) * t.z +
		(*this)(2, 3) * t.w;

	product.w =
		(*this)(3, 0) * t.x +
		(*this)(3, 1) * t.y +
		(*this)(3, 2) * t.z +
		(*this)(3, 3) * t.w;
	
	return product;
}

Ray Matrix::operator*(const Ray& r) {

	Tuple productOrig;
	Tuple productDir;
	
	Tuple o = r.origin();
	Tuple d = r.direction();

	productOrig.x =
		(*this)(0, 0) * o.x +
		(*this)(0, 1) * o.y +
		(*this)(0, 2) * o.z +
		(*this)(0, 3) * o.w;

	productOrig.y =
		(*this)(1, 0) * o.x +
		(*this)(1, 1) * o.y +
		(*this)(1, 2) * o.z +
		(*this)(1, 3) * o.w;

	productOrig.z =
		(*this)(2, 0) * o.x +
		(*this)(2, 1) * o.y +
		(*this)(2, 2) * o.z +
		(*this)(2, 3) * o.w;

	productOrig.w =
		(*this)(3, 0) * o.x +
		(*this)(3, 1) * o.y +
		(*this)(3, 2) * o.z +
		(*this)(3, 3) * o.w;

	productDir.x =
		(*this)(0, 0) * d.x +
		(*this)(0, 1) * d.y +
		(*this)(0, 2) * d.z +
		(*this)(0, 3) * d.w;

	productDir.y =
		(*this)(1, 0) * d.x +
		(*this)(1, 1) * d.y +
		(*this)(1, 2) * d.z +
		(*this)(1, 3) * d.w;

	productDir.z =
		(*this)(2, 0) * d.x +
		(*this)(2, 1) * d.y +
		(*this)(2, 2) * d.z +
		(*this)(2, 3) * d.w;

	productDir.w =
		(*this)(3, 0) * d.x +
		(*this)(3, 1) * d.y +
		(*this)(3, 2) * d.z +
		(*this)(3, 3) * d.w;

	return Ray(productOrig, productDir);
}

Matrix identity() {
	Matrix m(4, 4);
	m << 1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1;
	return m;
}

Matrix Matrix::transpose() const{

	Matrix m(row, col);
	
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			m(j, i) = (*this)(i, j);
		}
	}

	return m;
}

double Matrix::determinant() const{
	double det = 0;
	if (row == col && col == 2) {
		det =  (*this)(0, 0) * (*this)(1, 1) - (*this)(0, 1) * (*this)(1, 0);
	}
	else {
		for (int i = 0; i < col; i++) {
			det = det + (*this)(0, i) * cofactor(0, i);
		}	
	}
	return det;
}

Matrix Matrix::submatrix(unsigned r, unsigned c) const{
	Matrix m(row - 1, col - 1);

	int mrow, mcol;

	mrow = 0;
	for (int i = 0; i < row;i++) {
		mcol = 0;
		if (i == r) continue;
		for (int j = 0; j < col; j++) {
			if (j == c) continue;
			m(mrow, mcol) = (*this)(i, j);
			mcol++;
		}
		mrow++;
	}

	return m;
}

double Matrix::minor(unsigned r, unsigned c) const{

	return submatrix(r, c).determinant();

}

double Matrix::cofactor(unsigned r, unsigned c) const{
	if ((r + c) % 2 == 0) return minor(r, c);
	else return -minor(r, c);
}

bool Matrix::isInvertible() const {
	if (determinant() == 0) return false;
	return true;
}

Matrix Matrix::inverse() const {
	//if (!isInvertible()) exit(EXIT_FAILURE);

	Matrix inv(row, col);
	double det = (*this).determinant();

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			double c = (*this).cofactor(i, j);
			inv(j, i) = c / det;
		}
	}

	return inv;

}

/***************************************************/
//------ Transformation Methods ------------------//
/*************************************************/


Matrix translation(double x, double y, double z) {
	Matrix transform = identity();

	transform(0, 3) = x;
	transform(1, 3) = y;
	transform(2, 3) = z;

	return transform;
}

Matrix scale(double x, double y, double z) {
	Matrix transform = identity();

	transform(0, 0) = x;
	transform(1, 1) = y;
	transform(2, 2) = z;

	return transform;
}

Matrix rotationX(double rads) {
	Matrix transform = identity();

	transform(1, 1) = cos(rads);
	transform(1, 2) = -sin(rads);
	transform(2, 1) = sin(rads);
	transform(2, 2) = cos(rads);

	return transform;
}

Matrix rotationY(double rads) {
	Matrix transform = identity();

	transform(0, 0) = cos(rads);
	transform(0, 2) = sin(rads);
	transform(2, 0) = -sin(rads);
	transform(2, 2) = cos(rads);

	return transform;
}

Matrix rotationZ(double rads) {
	Matrix transform = identity();

	transform(0, 0) = cos(rads);
	transform(0, 1) = -sin(rads);
	transform(1, 0) = sin(rads);
	transform(1, 1) = cos(rads);

	return transform;
}

Matrix shear(double xy, double xz, double yx, double yz, double zx, double zy) {
	Matrix transform = identity();

	transform(0, 1) = xy;
	transform(0, 2) = xz;
	transform(1, 0) = yx;
	transform(1, 2) = yz;
	transform(2, 0) = zx;
	transform(2, 1) = zy;

	return transform;
}

Matrix view(Tuple from, Tuple to, Tuple up) {

	Tuple forward = (to - from).normalize();
	Tuple upNorm = up.normalize();
	Tuple left = forward.cross(upNorm);
	Tuple upTrue = left.cross(forward);

	Matrix orientation;
	orientation <<
		left.x, left.y, left.z, 0,
		upTrue.x, upTrue.y, upTrue.z, 0,
		-forward.x, -forward.y, -forward.z, 0,
		0, 0, 0, 1;

	return orientation * translation(-from.x, -from.y, -from.z);
}