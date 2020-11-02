#include "pch.h"

TEST(TransformTest, Translate) {

	Tuple p(-3, 4, 5, 1);
	Matrix transform = translation(5, -3, 2);
	Tuple result(2, 1, 7, 1);

	EXPECT_TRUE(transform * p == result);
}

TEST(TransformTest, TranslateInverse) {

	Tuple p(-3, 4, 5, 1);
	Matrix transform = translation(5, -3, 2);
	Tuple result(-8, 7, 3, 1);

	EXPECT_TRUE(transform.inverse() * p == result);
}

TEST(TransformTest, TranslateVec) {

	Tuple v(-3, 4, 5, 0);
	Matrix transform = translation(-5, 3, 2);
	Tuple result(-3, 4, 5, 0);

	EXPECT_TRUE(transform * v == result);
}

TEST(TransformTest, ScalePoint) {

	Tuple p(-4, 6, 8, 0);
	Matrix transform = scale(2, 3, 4);
	Tuple result(-8, 18, 32, 0);

	EXPECT_TRUE(transform * p == result);

}

TEST(TransformTest, ScaleVec) {

	Tuple v(-4, 6, 8, 1);
	Matrix transform = scale(2, 3, 4);
	Tuple result(-8, 18, 32, 1);

	EXPECT_TRUE(transform * v == result);

}

TEST(TransformTest, ScaleInverse) {

	Tuple p(-4, 6, 8, 0);
	Matrix transform = scale(2, 3, 4);
	Tuple result(-2, 2, 2, 0);

	EXPECT_TRUE(transform.inverse() * p == result);

}

TEST(TransformTest, Reflection) {

	Tuple p(-3, 2, 1, 0);
	Matrix transform = scale(-1, 1, 1);
	Tuple result(3, 2, 1, 0);

	EXPECT_TRUE(transform * p == result);
}

TEST(TransformTest, RotateX) {
	Tuple p(0, 1, 0, 1);
	Matrix eighth = rotationX(PI / 4);
	Matrix quarter = rotationX(PI / 2);
	Tuple result1(0, sqrt(2) / 2, sqrt(2) / 2, 1);
	Tuple result2(0, 0, 1, 1);

	EXPECT_TRUE(eighth * p == result1);
	EXPECT_TRUE(quarter * p ==  result2);

}

TEST(TransformTest, RotateXInv) {
	Tuple p(0, 1, 0, 1);
	Matrix quarter = rotationX(PI / 2);
	Tuple result2(0, 0, -1, 1);

	EXPECT_TRUE(quarter.inverse() * p == result2);

}

TEST(TransformTest, RotateY) {
	Tuple p(0, 0, 1, 1);
	Matrix eighth = rotationY(PI / 4);
	Matrix quarter = rotationY(PI / 2);
	Tuple result1(sqrt(2) / 2, 0, sqrt(2) / 2, 1);
	Tuple result2(1, 0, 0, 1);

	EXPECT_TRUE(eighth * p == result1);
	EXPECT_TRUE(quarter * p == result2);
}

TEST(TransformTest, RotateZ) {
	Tuple p(0, 1, 0, 1);
	Matrix eighth = rotationZ(PI / 4);
	Matrix quarter = rotationZ(PI / 2);
	Tuple result1(-sqrt(2) / 2, sqrt(2) / 2, 0,  1);
	Tuple result2(-1, 0, 0, 1);

	EXPECT_TRUE(eighth * p == result1);
	EXPECT_TRUE(quarter * p == result2);
}

TEST(TransformTest, ShearXY) {
	Matrix transform = shear(1, 0, 0, 0, 0, 0);
	Tuple p(2, 3, 4, 1);
	Tuple result(5, 3, 4, 1);

	EXPECT_TRUE(transform * p == result);
}

TEST(TransformTest, ShearXZ) {
	Matrix transform = shear(0, 1, 0, 0, 0, 0);
	Tuple p(2, 3, 4, 1);
	Tuple result(6, 3, 4, 1);

	EXPECT_TRUE(transform * p == result);
}

TEST(TransformTest, ShearYX) {
	Matrix transform = shear(0, 0, 1, 0, 0, 0);
	Tuple p(2, 3, 4, 1);
	Tuple result(2, 5, 4, 1);

	EXPECT_TRUE(transform * p == result);
}

TEST(TransformTest, ShearYZ) {
	Matrix transform = shear(0, 0, 0, 1, 0, 0);
	Tuple p(2, 3, 4, 1);
	Tuple result(2, 7, 4, 1);

	EXPECT_TRUE(transform * p == result);
}

TEST(TransformTest, ShearZX) {
	Matrix transform = shear(0, 0, 0, 0, 1, 0);
	Tuple p(2, 3, 4, 1);
	Tuple result(2, 3, 6, 1);

	EXPECT_TRUE(transform * p == result);
}

TEST(TransformTest, ShearZY) {
	Matrix transform = shear(0, 0, 0, 0, 0, 1);
	Tuple p(2, 3, 4, 1);
	Tuple result(2, 3, 7, 1);

	EXPECT_TRUE(transform * p == result);
}

TEST(TransformTest, Sequence) {
	Tuple p(1, 0, 1, 1);
	Tuple result(15, 0, 7, 1);
	Matrix A = rotationX(PI / 2);
	Matrix B = scale(5, 5, 5);
	Matrix C = translation(10, 5, 7);

	Tuple p1 = A * p;
	Tuple p2 = B * p1;
	Tuple p3 = C * p2;

	EXPECT_TRUE(p3 == result);
}

TEST(TransformTest, Chain) {
	Tuple p(1, 0, 1, 1);
	Tuple result(15, 0, 7, 1);
	Matrix A = rotationX(PI / 2);
	Matrix B = scale(5, 5, 5);
	Matrix C = translation(10, 5, 7);

	Matrix transform = C * B * A;
	
	EXPECT_TRUE(transform * p == result);
}