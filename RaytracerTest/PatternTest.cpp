#include "pch.h"
#include "../Raytracer/Pattern.h"
#include "../Raytracer/Pattern.cpp"
#include "../Raytracer/Light.h"
#include "../Raytracer/PointLight.h"
#include "../Raytracer/Sphere.h"

TEST(PatternTest, StripeConstruct) {
	Color black(0, 0, 0);
	Color white(1, 1, 1);
	stripePattern stripe = stripePattern(white, black);

	EXPECT_TRUE(stripe.a() == white);
	EXPECT_TRUE(stripe.b() == black);

}

TEST(PatternTest, StripeChangeY) {
	Color black(0, 0, 0);
	Color white(1, 1, 1);
	stripePattern stripe = stripePattern(white, black);

	EXPECT_TRUE(stripe.colorAt(point(0, 0, 0)) == white);
	EXPECT_TRUE(stripe.colorAt(point(0, 1, 0)) == white);
	EXPECT_TRUE(stripe.colorAt(point(0, 2, 0)) == white);
}

TEST(PatternTest, StripeChangeZ) {
	Color black(0, 0, 0);
	Color white(1, 1, 1);
	stripePattern stripe = stripePattern(white, black);

	EXPECT_TRUE(stripe.colorAt(point(0, 0, 0)) == white);
	EXPECT_TRUE(stripe.colorAt(point(0, 0, 1)) == white);
	EXPECT_TRUE(stripe.colorAt(point(0, 0, 2)) == white);
}

TEST(PatternTest, StripeChangeX) {
	Color black(0, 0, 0);
	Color white(1, 1, 1);
	stripePattern stripe = stripePattern(white, black);

	EXPECT_TRUE(stripe.colorAt(point(0, 0, 0)) == white);
	EXPECT_TRUE(stripe.colorAt(point(0.9, 0, 0)) == white);
	EXPECT_TRUE(stripe.colorAt(point(1, 0, 0)) == black);
	EXPECT_TRUE(stripe.colorAt(point(-0.1, 0, 0)) == black);
	EXPECT_TRUE(stripe.colorAt(point(-1, 0, 0)) == black);
	EXPECT_TRUE(stripe.colorAt(point(-1.1, 0, 0)) == white);
}

TEST(PatternTest, MaterialWithPattern) {
	Material m;
	m.pattern(stripePattern(Color(1, 1, 1), Color(0, 0, 0)));
	m.ambient(1);
	m.diffuse(0);
	m.specular(0);

	Tuple eyev = vec(0, 0, -1);
	Tuple normalv = vec(0, 0, -1);
	PointLight pl(point(0, 0, -10), Color(1, 1, 1));
	Sphere s;

	Color c1 = lighting(m, s, pl, point(0.9, 0, 0), eyev, normalv, false);
	Color c2 = lighting(m, s, pl, point(1.1, 0, 0), eyev, normalv, false);

	EXPECT_TRUE(c1 == Color(1, 1, 1));
	EXPECT_TRUE(c2 == Color(0, 0, 0));
}

TEST(PatternTest, PatternObjectSpace) {
	Color black(0, 0, 0);
	Color white(1, 1, 1);
	Sphere s;
	s.transform(scale(2, 2, 2));
	stripePattern stripes(white, black);
	Color c = stripes.colorAtObject(point(1.5, 0, 0), s);

	EXPECT_TRUE(c == white);
}

TEST(PatternTest, PatternObjectSpace2) {
	Color black(0, 0, 0);
	Color white(1, 1, 1);
	Sphere s;
	stripePattern stripes(white, black);
	stripes.transform(scale(2, 2, 2));
	Color c = stripes.colorAtObject(point(1.5, 0, 0), s);

	EXPECT_TRUE(c == white);
}

TEST(PatternTest, PatternObjectSpace3) {
	Color black(0, 0, 0);
	Color white(1, 1, 1);
	Sphere s;
	s.transform(scale(2, 2, 2));
	stripePattern stripes(white, black);
	stripes.transform(scale(0.5, 0, 0));
	Color c = stripes.colorAtObject(point(2.5, 0, 0), s);

	EXPECT_TRUE(c == white);
}


