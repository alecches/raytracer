#include "pch.h"

TEST(CsgTest, Constructor) {
	Sphere s;
	Cube c;
	CSG uni = CSG(operation::csgUnion, s, c);

	EXPECT_TRUE(s.parent() == &uni);
	EXPECT_TRUE(c.parent() == &uni);

}

TEST(CsgTest, UnionAllowables) {
	EXPECT_FALSE(intersectionAllowed(operation::csgUnion, true, true, true));
	EXPECT_TRUE(intersectionAllowed(operation::csgUnion, true, true, false));
	EXPECT_FALSE(intersectionAllowed(operation::csgUnion, true, false, true));
	EXPECT_TRUE(intersectionAllowed(operation::csgUnion, true, false, false));
	EXPECT_FALSE(intersectionAllowed(operation::csgUnion, false, true, true));
	EXPECT_FALSE(intersectionAllowed(operation::csgUnion, false, true, false));
	EXPECT_TRUE(intersectionAllowed(operation::csgUnion, false, false, true));
	EXPECT_TRUE(intersectionAllowed(operation::csgUnion, false, false, false));
}

TEST(CsgTest, IntersectAllowables) {
	EXPECT_TRUE(intersectionAllowed(operation::csgIntersect, true, true, true));
	EXPECT_FALSE(intersectionAllowed(operation::csgIntersect, true, true, false));
	EXPECT_TRUE(intersectionAllowed(operation::csgIntersect, true, false, true));
	EXPECT_FALSE(intersectionAllowed(operation::csgIntersect, true, false, false));
	EXPECT_TRUE(intersectionAllowed(operation::csgIntersect, false, true, true));
	EXPECT_TRUE(intersectionAllowed(operation::csgIntersect, false, true, false));
	EXPECT_FALSE(intersectionAllowed(operation::csgIntersect, false, false, true));
	EXPECT_FALSE(intersectionAllowed(operation::csgIntersect, false, false, false));
}

TEST(CsgTest, DifferenceAllowables) {
	EXPECT_FALSE(intersectionAllowed(operation::csgDifference, true, true, true));
	EXPECT_TRUE(intersectionAllowed(operation::csgDifference, true, true, false));
	EXPECT_FALSE(intersectionAllowed(operation::csgDifference, true, false, true));
	EXPECT_TRUE(intersectionAllowed(operation::csgDifference, true, false, false));
	EXPECT_TRUE(intersectionAllowed(operation::csgDifference, false, true, true));
	EXPECT_TRUE(intersectionAllowed(operation::csgDifference, false, true, false));
	EXPECT_FALSE(intersectionAllowed(operation::csgDifference, false, false, true));
	EXPECT_FALSE(intersectionAllowed(operation::csgDifference, false, false, false));
}

TEST(CsgTest, FilterIntersections) {

	Sphere s;
	Cube c;
	CSG uni = CSG(operation::csgUnion, s, c);
	CSG diff = CSG(operation::csgDifference, s, c);
	CSG inter = CSG(operation::csgIntersect, s, c);

	std::vector<Intersection> intu;
	intu.push_back(Intersection(1, uni.left()));
	intu.push_back(Intersection(2, uni.right()));
	intu.push_back(Intersection(3, uni.left()));
	intu.push_back(Intersection(4, uni.right()));
	std::vector<Intersection> uniInts = uni.filterIntersections(intu);

	std::vector<Intersection> intd;
	intd.push_back(Intersection(1, diff.left()));
	intd.push_back(Intersection(2, diff.right()));
	intd.push_back(Intersection(3, diff.left()));
	intd.push_back(Intersection(4, diff.right()));
	std::vector<Intersection> diffInts = diff.filterIntersections(intd);

	std::vector<Intersection> inti;
	inti.push_back(Intersection(1, inter.left()));
	inti.push_back(Intersection(2, inter.right()));
	inti.push_back(Intersection(3, inter.left()));
	inti.push_back(Intersection(4, inter.right()));
	std::vector<Intersection> interInts = inter.filterIntersections(inti);

	EXPECT_EQ(uniInts.size(), 2);
	EXPECT_TRUE(uniInts[0].t == intu[0].t);
	EXPECT_TRUE(uniInts[1].t == intu[3].t);

	EXPECT_EQ(diffInts.size(), 2);
	EXPECT_TRUE(diffInts[0].t == intd[0].t);
	EXPECT_TRUE(diffInts[1].t == intd[1].t);

	EXPECT_EQ(interInts.size(), 2);
	EXPECT_TRUE(interInts[0].t == inti[1].t);
	EXPECT_TRUE(interInts[1].t == inti[2].t);

}

TEST(CsgTest, Miss) {
	CSG shape = CSG(operation::csgUnion, Sphere(), Cube());
	Ray r(point(0, 2, -5), vec(0, 0, 1));
	std::vector<Intersection> intx;
	shape.localIntersect(r, intx);
	EXPECT_EQ(intx.size(), 0);
}

TEST(CsgTest, Hit) {
	Sphere s1;
	Sphere s2;
	s2.transform(translation(0, 0, 0.5));
	CSG shape = CSG(operation::csgUnion, s1, s2);
	Ray r(point(0, 0, -5), vec(0, 0, 1));
	std::vector<Intersection> intx;
	shape.localIntersect(r, intx);

	EXPECT_EQ(intx.size(), 2);
	EXPECT_EQ(intx[0].t, 4);
	EXPECT_EQ(intx[1].t, 6.5);
}
