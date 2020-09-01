#include "pch.h"
#include "../Raytracer/Color.h"
#include "../Raytracer/Color.cpp"

TEST(ColorTest, Constructor) {
	Color c(0.8, 0.4, 1.2);

	EXPECT_EQ(c.red, 0.8);
	EXPECT_EQ(c.green, 0.4);
	EXPECT_EQ(c.blue, 1.2);
}

TEST(ColorTest, Addition) {
	Color c1(0.3, 0.2, 0.15);
	Color c2(0.32, 0.6, 0.4);
	Color result(0.62, 0.8, 0.55);

	EXPECT_TRUE(c1 + c2 == result);

}

TEST(ColorTest, Subtraction) {
	Color c1(0.3, 0.2, 0.15);
	Color c2(0.32, 0.6, 0.4);
	Color result(0.02, 0.4, 0.25);

	EXPECT_TRUE(c2 - c1 == result);
}

TEST(ColorTest, Scale) {
	Color c(0.2, 0.34, 0.15);
	double s = 2;
	Color result(0.4, 0.68, 0.3);

	EXPECT_TRUE(c * s == result);

}

TEST(ColorTest, Multiply) {
	Color c1(1, 0.5, 1);
	Color c2(0.32, 0.8, 0.4);
	Color result(0.32, 0.4, 0.4);

	EXPECT_TRUE(c1 * c2 == result);
}
