#include "pch.h"
#include "../Raytracer/Matrix.h"
#include "../Raytracer/Matrix.cpp"
#include "../Raytracer/Util.h"

TEST(MatrixTest, Decl44) {
	Matrix mat(4, 4);
	mat <<
	1, 2, 3, 4,
	5.5, 6.5, 7.5, 8.5,
	9, 10, 11, 12,
	13.5, 14.5, 15.5, 16.5;
	
	EXPECT_EQ(mat(0, 0), 1);
	EXPECT_EQ(mat(1, 2), 7.5);
	EXPECT_EQ(mat(3, 3), 16.5);

}

TEST(MatrixTest, Decl22) {
	Matrix mat(2, 2);
	mat << 1, 2,
		   3, 4;


	EXPECT_EQ(mat(0, 0), 1);
	EXPECT_EQ(mat(1, 0), 3);
	EXPECT_EQ(mat(0, 1), 2);
	EXPECT_EQ(mat(1, 1), 4);

}

TEST(MatrixTest, Decl33) {
	Matrix mat(3, 3);
	mat << 1.5, -2, 3.4,
		5, 3.45, 6.7,
		-1, 1, 0;

	EXPECT_EQ(mat(0, 0), 1.5);
	EXPECT_EQ(mat(0, 1), -2);
	EXPECT_EQ(mat(0, 2), 3.4);
	EXPECT_EQ(mat(1, 0), 5);
	EXPECT_EQ(mat(1, 1), 3.45);
	EXPECT_EQ(mat(1, 2), 6.7);
	EXPECT_EQ(mat(2, 0), -1);
	EXPECT_EQ(mat(2, 1), 1);
	EXPECT_EQ(mat(2, 2), 0);

}

TEST(MatrixTest, Equality) {
	Matrix m1(4, 4);
	Matrix m2(4, 4);

	m1 << 9, 8, 7, 6,
		5, 4, 3, 2,
		1, 2, 3, 4,
		5, 6, 7, 8;

	m2 << 9, 8, 7, 6,
		5, 4, 3, 2,
		1, 2, 3, 4,
		5, 6, 7, 8;

	EXPECT_TRUE(m1 == m2);
}

TEST(MatrixTest, Inequality) {
	Matrix m1(4, 4);
	Matrix m2(4, 4);

	m1 << 9, 8, 7, 6,
		5, 4, 3, 2,
		1, 2, 3, 4,
		5, 6, 7, 8;

	m2 << 9, 8, 7, 6,
		5, 4, 3, 2,
		1, 3, 2, 4,
		5, 6, 7, 8;

	EXPECT_FALSE(m1 == m2);
}

TEST(MatrixTest, Multiply) {
	Matrix m1(4, 4);
	Matrix m2(4, 4);
	Matrix result(4, 4);

	m1 << 1, 2, 3, 4,
		5, 6, 7, 8,
		9, 8, 7, 6,
		5, 4, 3, 2;

	m2 <<
		-2, 1, 2, 3,
		3, 2, 1, -1,
		4, 3, 6, 5,
		1, 2, 7, 8;

	result <<
		20, 22, 50, 48,
		44, 54, 114, 108,
		40, 58, 110, 102,
		16, 26, 46, 42;

	EXPECT_TRUE(m1 * m2 == result);


}

TEST(MatrixTest, MultiplyTuple) {
	Matrix m1(4, 4);
	Tuple t(1, 2, 3, 1);
	Tuple result(18, 24, 33, 1);
	m1 <<
		1, 2, 3, 4,
		2, 4, 4, 2,
		8, 6, 4, 1,
		0, 0, 0, 1;

	EXPECT_TRUE(m1 * t == result);

}

TEST(MatrixTest, Identity) {
	Matrix ident = Matrix::identity();
	Matrix m(4, 4);
	m <<
		0, 1, 5, 10,
		23, -1, 0, 0,
		1, 1, 1, 1,
		92, 4, 3 - 20;

	EXPECT_TRUE(m * ident == m);
}

TEST(MatrixTest, IdentityTuple) {
	Matrix ident = Matrix::identity();
	Tuple t(0, 3, 2, -1);

	EXPECT_TRUE(ident * t == t);
}

TEST(MatrixTest, Transpose) {
	Matrix m(4, 4);
	Matrix result(4, 4);
	m <<
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 8, 7, 6,
		5, 4, 3, 2;

	result <<
		1, 5, 9, 5,
		2, 6, 8, 4,
		3, 7, 7, 3,
		4, 8, 6, 2;

	EXPECT_TRUE(m.transpose() == result);
}

TEST(MatrixTest, TransposeIdentity) {
	Matrix ident = Matrix::identity();
	EXPECT_TRUE(ident.transpose() == ident);
}

TEST(MatrixTest, Determinant2x2) {
	Matrix m(2, 2);
	m <<
		1, 5,
		-3, 2;

	EXPECT_EQ(m.determinant(), 17);
}

TEST(MatrixTest, Submatrix3x3) {
	Matrix m(3, 3);
	Matrix result(2, 2);
	m <<
		1, 5, 0,
		-3, 2, 7,
		0, 6, -3;
	result <<
		-3, 2,
		0, 6;

	EXPECT_TRUE(m.submatrix(0, 2) == result);
}

TEST(MatrixTest, Submatrix4x4) {
	Matrix m(4, 4);
	Matrix result(3, 3);
	m <<
		-6, 1, 1, 6,
		-8, 5, 8, 6,
		-1, 0, 8, 2,
		-7, 1, -1, 1;
	result <<
		-6, 1, 6,
		-8, 8, 6,
		-7, -1, 1;

	EXPECT_TRUE(m.submatrix(2, 1) == result);
}

TEST(MatrixTest, Minor3x3) {
	Matrix m(3, 3);
	m <<
		3, 5, 0,
		2, -1, -7,
		6, -1, 5;
	Matrix sub = m.submatrix(1,0);
	EXPECT_TRUE(sub.determinant() == 25);
	EXPECT_TRUE(m.minor(1, 0) == 25);
}

TEST(MatrixTest, Cofactor3x3) {
	Matrix m(3, 3);
	m <<
		3, 5, 0,
		2, -1, -7,
		6, -1, 5;

	EXPECT_EQ(m.minor(0, 0), -12);
	EXPECT_EQ(m.cofactor(0, 0), -12);
	EXPECT_EQ(m.minor(1, 0), 25);
	EXPECT_EQ(m.cofactor(1, 0), -25);

}

TEST(MatrixTest, Determinant3x3) {
	Matrix m(3, 3);
	m <<
		1, 2, 6,
		-5, 8, -4,
		2, 6, 4;

	EXPECT_EQ(m.cofactor(0, 0), 56);
	EXPECT_EQ(m.cofactor(0, 1), 12);
	EXPECT_EQ(m.cofactor(0, 2), -46);
	EXPECT_EQ(m.determinant(), -196);

}

TEST(MatrixTest, Determinant4x4) {
	Matrix m(4, 4);
	m <<
		-2, -8, 3, 5,
		-3, 1, 7, 3,
		1, 2, -9, 6,
		-6, 7, 7, -9;


	EXPECT_EQ(m.cofactor(0, 0), 690);
	EXPECT_EQ(m.cofactor(0, 1), 447);
	EXPECT_EQ(m.cofactor(0, 2), 210);
	EXPECT_EQ(m.cofactor(0, 3), 51);
	EXPECT_EQ(m.determinant(), -4071);

}

TEST(MatrixTest, Inverse) {
	Matrix m(4, 4);
	Matrix result(4, 4);
	m <<
		-5, 2, 6, -8,
		1, -5, 1, 8,
		7, 7, -6, -7,
		1, -3, 7, 4;
	result <<
		0.21805, 0.45113, 0.24060, -0.04511,
		-0.80827, -1.45677, -0.44361, 0.52068,
		-0.07895, -0.22368, -0.05263, 0.19737,
		-0.52256, -0.81391, -0.30075, 0.30639;

	Matrix inv = m.inverse();

	EXPECT_EQ(m.determinant(), 532);
	EXPECT_EQ(m.cofactor(2, 3), -160);
	EXPECT_EQ(inv(3, 2),-160.0 / 532.0);
	EXPECT_EQ(m.cofactor(3, 2), 105);
	EXPECT_EQ(inv(2, 3),105.0 / 532.0);
	EXPECT_TRUE(inv == result);
	
}