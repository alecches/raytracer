#include "pch.h"

TEST(ShadowTest, InShadow) {
	Tuple eyev(vec(0, 0, -1));
	Tuple normalv(vec(0, 0, -1));
	PointLight light(point(0, 0, -10), Color(1, 1, 1));
	bool shadow = true;
	Material m;
	Sphere s;

	Color c = lighting(m, s, light, point(0,0,0), eyev, normalv, shadow);
	EXPECT_TRUE(c == Color(0.1, 0.1, 0.1));
}

TEST(ShadowTest, PathClear) {
	World w = defaultWorld();
	Tuple p = point(0, 10, 0);
	EXPECT_FALSE(inShadow(w, p));
}

TEST(ShadowTest, PathObscured) {
	World w = defaultWorld();
	Tuple p = point(10, -10, 10);
	EXPECT_TRUE(inShadow(w, p));
}

TEST(ShadowTest, LightBetween) {
	World w = defaultWorld();
	Tuple p = point(-20, 20, -20);
	EXPECT_FALSE(inShadow(w, p));
}

TEST(ShadowTest, PointBetween) {
	World w = defaultWorld();
	Tuple p = point(-2, 2, -2);
	EXPECT_FALSE(inShadow(w, p));
}

TEST(ShadowTest, ShadeHitShadow) {
	World w;
	w.addLight(PointLight(point(0, 0, -10), Color(1, 1, 1)));
	Sphere s1;
	w.addObject(s1);
	Sphere s2;
	s2.transform(translation(0, 0, 10));
	w.addObject(s2);

	Ray r(point(0, 0, 5), vec(0, 0, 1));
	Intersection i(4, s2);
	IntersectInfo iInf(i, r);
	Color c = shadeHit(w, iInf);

	EXPECT_TRUE(c == Color(0.1, 0.1, 0.1));

}

TEST(ShadowTest, Offset) {
	Ray r(point(0, 0, - 5), vec(0, 0, 1));
	Sphere s;
	s.transform(translation(0, 0, 1));

	Intersection i(5, s);
	IntersectInfo iInf(i, r);

	EXPECT_TRUE(iInf.overPoint.z < -Epsilon / 2);
	EXPECT_TRUE(iInf.overPoint.z < iInf.point.z);

}