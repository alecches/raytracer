#include "pch.h"
#include "../Raytracer/Color.h"
#include "../Raytracer/Canvas.h"
#include "../Raytracer/Canvas.cpp"

TEST(CanvasTest, Constructor) {
	Canvas c(10, 20);
	Color black;

	EXPECT_EQ(c.width, 10);
	EXPECT_EQ(c.height, 20);

	for (int i = 0; i < c.width; i++) {
		for (int j = 0; j < c.height; j++) {
			EXPECT_TRUE(c.getPixel(i, j) == black);
		}
	}

}

TEST(CanvasTest, WritePixel) {
	Canvas c(10, 20);
	Color red(1, 0, 0);

	c.writePixel(3, 5, red);
	EXPECT_TRUE(red == c.getPixel(3, 5));
}