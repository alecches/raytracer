#include "pch.h"

TEST(PlaneTest, Normal) {
	Plane p;
	Tuple n1 = p.normalAt(point(0, 0, 0), Intersection(0, &p));
	Tuple n2 = p.normalAt(point(10, 0, -10), Intersection(0, &p));
	Tuple n3 = p.normalAt(point(-5, 0, 150), Intersection(0, &p));

	EXPECT_TRUE(n1 == vec(0, 1, 0));
	EXPECT_TRUE(n2 == vec(0, 1, 0));
	EXPECT_TRUE(n3 == vec(0, 1, 0));
}

TEST(PlaneTest, IntersectParallel) {
	Plane p;
	Ray r(point(0, 10, 0), vec(0, 0, 1));
	std::vector<Intersection> intx;
	intersect(r, p, intx);
	EXPECT_EQ(intx.size(), 0);
}

TEST(PlaneTest, IntersectCoplanar) {
	Plane p;
	Ray r(point(0, 0, 0), vec(0, 0, 1));
	std::vector<Intersection> intx;
	intersect(r, p, intx);
	EXPECT_EQ(intx.size(), 0);
}

TEST(PlaneTest, IntersectAbove) {
	Plane p;
	Ray r(point(0, 1, 0), vec(0, -1, 0));
	std::vector<Intersection> intx;
	intersect(r, p, intx);
	EXPECT_EQ(intx.size(), 1);
	EXPECT_TRUE(intx[0].t == 1);
	EXPECT_TRUE(intx[0].object == &p);
}

TEST(PlaneTest, IntersectBelow) {
	Plane p;
	Ray r(point(0, -1, 0), vec(0, 1, 0));
	std::vector<Intersection> intx;
	intersect(r, p, intx);
	EXPECT_EQ(intx.size(), 1);
	EXPECT_TRUE(intx[0].t == 1);
	EXPECT_TRUE(intx[0].object == &p);
}