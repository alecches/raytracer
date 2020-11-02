#include "pch.h"

TEST(CanvasTest, Constructor) {
	Canvas c(10, 20);
	Color black;

	EXPECT_EQ(c.width(), 10);
	EXPECT_EQ(c.height(), 20);

	for (int i = 0; i < c.width(); i++) {
		for (int j = 0; j < c.height(); j++) {
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


TEST(CanvasTest, HeaderPPM) {
	Canvas c(5, 3);
	std::string ppm = c.toPPM();

	std::stringstream ss(ppm);
	std::string str;
	
	std::getline(ss, str, '\n');
	EXPECT_EQ(str, "P3");
	std::getline(ss, str, '\n');
	EXPECT_EQ(str, "5 3");
	std::getline(ss, str, '\n');
	EXPECT_EQ(str, "255");

}

TEST(CanvasTest, BodyPPM) {
	Canvas c(5, 3);
	Color c1(1.5,0 ,0);
	Color c2(0, 0.5, 0);
	Color c3(-0.5, 0, 1);
	c.writePixel(0, 0, c1);
	c.writePixel(2, 1, c2);
	c.writePixel(4, 2, c3);

	std::string ppm = c.toPPM();
	std::stringstream ss(ppm);
	std::string str;

	for (int i = 0; i < 3; i++) {
		std::getline(ss, str, '\n');
	}

	std::string str1 = "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0";
	std::string str2 = "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0";
	std::string str3 = "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255";

	std::getline(ss, str, '\n');
	EXPECT_EQ(str, str1);
	std::getline(ss, str, '\n');
	EXPECT_EQ(str, str2);
	std::getline(ss, str, '\n');
	EXPECT_EQ(str, str3);

}

TEST(CanvasTest, OverflowPPM) {

	Canvas c(10, 2);
	Color c1(1, 0.8, 0.6);
	for (int y = 0; y < 2; y++) {
		for (int x = 0; x < 10; x++) {
			c.writePixel(x, y, c1);
		}
	}

	std::string ppm = c.toPPM();
	std::stringstream ss(ppm);
	std::string str;

	for (int i = 0; i < 3; i++) {
		std::getline(ss, str, '\n');
	}

	std::string str1 = "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204";
	std::string str2 = "153 255 204 153 255 204 153 255 204 153 255 204 153";

	std::getline(ss, str, '\n');
	EXPECT_EQ(str, str1);
	std::getline(ss, str, '\n');
	EXPECT_EQ(str, str2);
	std::getline(ss, str, '\n');
	EXPECT_EQ(str, str1);
	std::getline(ss, str, '\n');
	EXPECT_EQ(str, str2);
	
}
