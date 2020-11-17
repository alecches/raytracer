#include "pch.h"

class PatternTest : public ::testing::Test {
protected:

	void SetUp() override {
		black = Color(0, 0, 0);
		white = Color(1, 1, 1);
	}

	Color black;
	Color white;
};

TEST_F(PatternTest, StripeConstruct) {
	stripePattern stripe = stripePattern(white, black);

	EXPECT_TRUE(stripe.a() == white);
	EXPECT_TRUE(stripe.b() == black);
}

TEST_F(PatternTest, StripeChangeY) {

	stripePattern stripe = stripePattern(white, black);

	EXPECT_TRUE(stripe.colorAt(point(0, 0, 0)) == white);
	EXPECT_TRUE(stripe.colorAt(point(0, 1, 0)) == white);
	EXPECT_TRUE(stripe.colorAt(point(0, 2, 0)) == white);
}

TEST_F(PatternTest, StripeChangeZ) {

	stripePattern stripe = stripePattern(white, black);

	EXPECT_TRUE(stripe.colorAt(point(0, 0, 0)) == white);
	EXPECT_TRUE(stripe.colorAt(point(0, 0, 1)) == white);
	EXPECT_TRUE(stripe.colorAt(point(0, 0, 2)) == white);
}

TEST_F(PatternTest, StripeChangeX) {

	stripePattern stripe = stripePattern(white, black);

	EXPECT_TRUE(stripe.colorAt(point(0, 0, 0)) == white);
	EXPECT_TRUE(stripe.colorAt(point(0.9, 0, 0)) == white);
	EXPECT_TRUE(stripe.colorAt(point(1, 0, 0)) == black);
	EXPECT_TRUE(stripe.colorAt(point(-0.1, 0, 0)) == black);
	EXPECT_TRUE(stripe.colorAt(point(-1, 0, 0)) == black);
	EXPECT_TRUE(stripe.colorAt(point(-1.1, 0, 0)) == white);
}

TEST_F(PatternTest, MaterialWithPattern) {
	Material m;
	m.pattern(stripePattern(white, black));
	m.ambient(1);
	m.diffuse(0);
	m.specular(0);

	Tuple eyev = vec(0, 0, -1);
	Tuple normalv = vec(0, 0, -1);
	PointLight pl(point(0, 0, -10), Color(1, 1, 1));
	Sphere s;

	Color c1 = lighting(m, s, pl, point(0.9, 0, 0), eyev, normalv, false);
	Color c2 = lighting(m, s, pl, point(1.1, 0, 0), eyev, normalv, false);

	EXPECT_TRUE(c1 == white);
	EXPECT_TRUE(c2 == black);
}

TEST_F(PatternTest, PatternObjectSpace) {

	Sphere s;
	s.transform(scale(2, 2, 2));
	stripePattern stripes(white, black);
	Color c = stripes.colorAtObject(point(1.5, 0, 0), s);

	EXPECT_TRUE(c == white);
}

TEST_F(PatternTest, PatternObjectSpace2) {

	Sphere s;
	stripePattern stripes(white, black);
	stripes.transform(scale(2, 2, 2));
	Color c = stripes.colorAtObject(point(1.5, 0, 0), s);

	EXPECT_TRUE(c == white);
}

TEST_F(PatternTest, PatternObjectSpace3) {

	Sphere s;
	s.transform(scale(2, 2, 2));
	stripePattern stripes(white, black);
	stripes.transform(scale(0.5, 0, 0));
	Color c = stripes.colorAtObject(point(2.5, 0, 0), s);

	EXPECT_TRUE(c == white);
}

TEST_F(PatternTest, Gradient) {

	gradientPattern gradient = gradientPattern(white, black);

	EXPECT_TRUE(gradient.colorAt(point(0, 0, 0)) == white);
	EXPECT_TRUE(gradient.colorAt(point(0.25, 0, 0)) == Color(0.75, 0.75, 0.75));
	EXPECT_TRUE(gradient.colorAt(point(0.5, 0, 0)) == Color(0.5, 0.5, 0.5));
	EXPECT_TRUE(gradient.colorAt(point(0.75, 0, 0)) == Color(0.25, 0.25, 0.25));

}

TEST_F(PatternTest, Ring) {

	ringPattern ring = ringPattern(white, black);

	EXPECT_TRUE(ring.colorAt(point(0, 0, 0)) == white);
	EXPECT_TRUE(ring.colorAt(point(1, 0, 0)) == black);
	EXPECT_TRUE(ring.colorAt(point(0, 0, 1)) == black);
	EXPECT_TRUE(ring.colorAt(point(0.708, 0, 0.708)) == black);
}

TEST_F(PatternTest, CheckerX) {
	checkerPattern checkers = checkerPattern(white, black);

	EXPECT_TRUE(checkers.colorAt(point(0, 0, 0)) == white);
	EXPECT_TRUE(checkers.colorAt(point(0.99, 0, 0)) == white);
	EXPECT_TRUE(checkers.colorAt(point(1.01, 0, 0)) == black);
}

TEST_F(PatternTest, CheckerY) {
	checkerPattern checkers = checkerPattern(white, black);

	EXPECT_TRUE(checkers.colorAt(point(0, 0, 0)) == white);
	EXPECT_TRUE(checkers.colorAt(point(0, 0.99, 0)) == white);
	EXPECT_TRUE(checkers.colorAt(point(0, 1.01, 0)) == black);
}

TEST_F(PatternTest, CheckerZ) {
	checkerPattern checkers = checkerPattern(white, black);

	EXPECT_TRUE(checkers.colorAt(point(0, 0, 0)) == white);
	EXPECT_TRUE(checkers.colorAt(point(0, 0, 0.99)) == white);
	EXPECT_TRUE(checkers.colorAt(point(0, 0, 1.01)) == black);
}


