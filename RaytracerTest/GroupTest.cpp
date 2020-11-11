#include "pch.h"

TEST(GroupTest, Constructor) {
	Group g;
	EXPECT_TRUE(g.transform() == identity());
	EXPECT_EQ(g.children().size(), 0);
}

TEST(GroupTest, ParentAttribute) {
	Sphere s;
	EXPECT_TRUE(s.parent() == nullptr);
}

TEST(GroupTest, AddChild) {
	Group g;
	Sphere s;
	g.addChild(s);
	EXPECT_EQ(g.children().size(), 1);
	//EXPECT_TRUE(g.children().front() == &s);
	EXPECT_TRUE(s.parent() == &g);
}

TEST(GroupTest, IntersectEmpty) {
	Group g;
	Ray r(point(0, 0, 0), vec(0, 0, 1));
	std::vector < Intersection> intx;
	g.localIntersect(r, intx);
	EXPECT_EQ(intx.size(), 0);
}

TEST(GroupTest, IntersectNonempty) {
	Group g;
	Sphere s1;
	Sphere s2;
	s2.transform(translation(0, 0, -3));
	Sphere s3;
	s3.transform(translation(5, 0, 0));
	g.addChild(s1);
	g.addChild(s2);
	g.addChild(s3);
	Ray r(point(0, 0, -5), vec(0, 0, 1));
	std::vector<Intersection> intx;
	g.localIntersect(r, intx);
	
	EXPECT_EQ(intx.size(), 4);
	EXPECT_TRUE(intx[2].object == &s2);
	EXPECT_TRUE(intx[3].object == &s2);
	EXPECT_TRUE(intx[0].object == &s1);
	EXPECT_TRUE(intx[1].object == &s1);
}

TEST(GroupTest, GroupTransforms) {
	Group g;
	g.transform(scale(2, 2, 2));
	Sphere s;
	s.transform(translation(5, 0, 0));
	g.addChild(s);
	Ray r(point(10, 0, -10), vec(0, 0, 1));
	std::vector<Intersection> intx;
	intersect(r, g, intx);
	EXPECT_EQ(intx.size(), 2);
}

TEST(GroupTest, WorldToObjectSpace) {
	Group g1;
	g1.transform(rotationY(PI / 2));
	Group g2;
	g2.transform(scale(2, 2, 2));
	g1.addChild(g2);
	Sphere s;
	s.transform(translation(5, 0, 0));
	g2.addChild(s);
	Tuple p = worldToObject(point(-2, 0, -10), s);
	EXPECT_TRUE(p == point(0, 0, -1));
}

TEST(GroupTest, NormalToWorldSpace) {
	Group g1;
	g1.transform(rotationY(PI / 2));
	Group g2;
	g2.transform(scale(1, 2, 3));
	g1.addChild(g2);
	Sphere s;
	s.transform(translation(5, 0, 0));
	g2.addChild(s);
	Tuple norm = normalToWorld(vec(sqrt(3)/3,sqrt(3)/3,sqrt(3)/3), s);
	EXPECT_TRUE(norm == vec(0.28571, 0.42857, -0.85714));
}

TEST(GroupTest, NormalOnObjectInGroup) {
	Group g1;
	g1.transform(rotationY(PI / 2));
	Group g2;
	g2.transform(scale(1, 2, 3));
	g1.addChild(g2);
	Sphere s;
	s.transform(translation(5, 0, 0));
	g2.addChild(s);
	Tuple norm = normalAt(point(1.7321, 1.1547, -5.5774), s);
	EXPECT_TRUE(norm == vec(0.28570, 0.42854, -0.85716));
}
