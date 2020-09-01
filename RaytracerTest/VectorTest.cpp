#include "pch.h"
#include "../Raytracer/Tuple.h"
#include "../Raytracer/TupleFactory.h"

TEST(VectorTest, Magnitude100) {
	Tuple v(1, 0, 0, 0);
	EXPECT_EQ(v.magnitude(), 1);
}

TEST(VectorTest, Magnitude010) {
	Tuple v(0, 1, 0, 0);
	EXPECT_EQ(v.magnitude(), 1);
}

TEST(VectorTest, Magnitude001) {
	Tuple v(0, 0, 1, 0);
	EXPECT_EQ(v.magnitude(), 1);
}

TEST(VectorTest, Magnitude123) {
	Tuple v(1, 2, 3, 0);
	EXPECT_EQ(v.magnitude(), sqrt(14));
}

TEST(VectorTest, Magnitude123Negative) {
	Tuple v(-1, -2, -3, 0);
	EXPECT_EQ(v.magnitude(), sqrt(14));
}

TEST(VectorTest, Normalize400) {
	Tuple v(4, 0, 0, 0);
	Tuple result(1, 0, 0, 0);
	EXPECT_TRUE(v.normalize().equals(result));
}

TEST(VectorTest, Normalize123) {
	Tuple v(1, 2, 3, 0);
	Tuple result(1 / sqrt(14), 2 / sqrt(14), 3 / sqrt(14), 0);
	EXPECT_TRUE(v.normalize().equals(result));
}

TEST(VectorTest, NormalizedMagnitude) {
	Tuple v(1, 2, 3, 0);
	EXPECT_EQ(1, v.normalize().magnitude());
}

TEST(VectorTest, DotProduct) {
	Tuple v1(1, 2, 3, 0);
	Tuple v2(2, 3, 4, 0);

	EXPECT_EQ(v1.dot(v2), 20);
}

TEST(VectorTest, CrossProduct) {
	Tuple v1(1, 2, 3, 0);
	Tuple v2(2, 3, 4, 0);
	Tuple result1(-1, 2, -1, 0);
	Tuple result2(1, -2, 1, 0);

	EXPECT_TRUE(v1.cross(v2).equals(result1));
	EXPECT_TRUE(v2.cross(v1).equals(result2));
}