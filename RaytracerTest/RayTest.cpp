#include "pch.h"
#include "../Raytracer/Ray.h"
#include "../Raytracer/Ray.cpp"
#include "../Raytracer/TupleFactory.h"
#include "../Raytracer/Sphere.h"
#include "../Raytracer/Sphere.cpp"
#include "../Raytracer/Intersection.h"
#include "../Raytracer/Intersection.cpp"
#include "../Raytracer/Matrix.h"


TEST(RayTest, Constructor) {
	Tuple p(1, 2, 3, 1);
	Tuple v(4, 5, 6, 0);

	Ray r = Ray(p, v);
	
	EXPECT_TRUE(r.origin() == p);
	EXPECT_TRUE(r.direction() == v);

}

TEST(RayTest, Intersect1) {
	Ray r = Ray(point(0, 0, -5), vec(0, 0, 1));
	Sphere s;
	std::deque<Intersection> intersections = r.intersect(s);

	EXPECT_EQ(intersections[0].t, 4);
	EXPECT_EQ(intersections[1].t, 6);
}

TEST(RayTest, Intersect2) {
	Ray r = Ray(point(0, 1, -5), vec(0, 0, 1));
	Sphere s;
	std::deque<Intersection> intersections = r.intersect(s);

	EXPECT_EQ(intersections[0].t, 5);
	EXPECT_EQ(intersections[1].t, 5);
}

TEST(RayTest, Intersect3) {
	Ray r = Ray(point(0, 2, -5), vec(0, 0, 1));
	Sphere s;
	std::deque<Intersection> intersections = r.intersect(s);

	EXPECT_EQ(intersections.size(), 0);
}

TEST(RayTest, Intersect4) {
	Ray r = Ray(point(0, 0, 0), vec(0, 0, 1));
	Sphere s;
	std::deque<Intersection> intersections = r.intersect(s);

	EXPECT_EQ(intersections[0].t, -1);
	EXPECT_EQ(intersections[1].t, 1);
}

TEST(RayTest, Intersect5) {
	Ray r = Ray(point(0, 0, 5), vec(0, 0, 1));
	Sphere s;
	std::deque<Intersection> intersections = r.intersect(s);

	EXPECT_EQ(intersections[0].t, -6);
	EXPECT_EQ(intersections[1].t, -4);
}

TEST(RayTest, IntersectionType) {
	Sphere s;
	Intersection i = Intersection(3.5, s);
	EXPECT_EQ(i.t, 3.5);
	EXPECT_EQ(i.object, &s);
}

TEST(RayTest, IntersectObjSet) {

	Ray r = Ray(point(0, 0, 5), vec(0, 0, 1));
	Sphere s;
	std::deque<Intersection> intersections = r.intersect(s);

	EXPECT_EQ(intersections.size(), 2);
	EXPECT_EQ(intersections[0].object, &s);
	EXPECT_EQ(intersections[1].object, &s);


}

TEST(RayTest, HitPosT) {

	Sphere s;
	std::deque<Intersection> ints{ Intersection(1,s),Intersection{2,s} };
	EXPECT_TRUE(ints[hit(ints)] == ints[0]);
	
}

TEST(RayTest, HitPosNegT) {

	Sphere s;
	std::deque<Intersection> ints{ Intersection(-1,s),Intersection{2,s} };
	EXPECT_TRUE(ints[hit(ints)] == ints[1]);

}

TEST(RayTest, HitNegT) {

	Sphere s;
	std::deque<Intersection> ints{ Intersection(-2,s),Intersection{-1,s} };
	EXPECT_TRUE(hit(ints) == -1);

}

TEST(RayTest, HitMore) {

	Sphere s;
	std::deque<Intersection> ints{ Intersection(5,s),Intersection{7,s},Intersection(-3,s),Intersection{2,s} };
	EXPECT_TRUE(ints[hit(ints)] == ints[3]);

}

TEST(RayTest, Translate) {

	Ray r(point(1, 2, 3), vec(0, 1, 0));
	Matrix m = translation(3, 4, 5);
	Ray r2 = m * r;

	EXPECT_TRUE(r2.origin() == point(4, 6, 8));
	EXPECT_TRUE(r2.direction() == vec(0, 1, 0));
}

TEST(RayTest, Scale) {

	Ray r(point(1, 2, 3), vec(0, 1, 0));
	Matrix m = scale(2, 3, 4);
	Ray r2 = m * r;

	EXPECT_TRUE(r2.origin() == point(2, 6, 12));
	EXPECT_TRUE(r2.direction() == vec(0, 3, 0));
}

TEST(RayTest, SphereTransform) {
	Sphere s;
	EXPECT_TRUE(s.transform() == identity());
}

TEST(RayTest, SphereSetT) {
	Sphere s;
	s.transform(translation(2, 3, 4));
	EXPECT_TRUE(s.transform() == translation(2, 3, 4));
}

TEST(RayTest, ScaledSphereIntersection) {
	Sphere s;
	Ray r(point(0, 0, -5), vec(0, 0, 1));
	s.transform(scale(2, 2, 2));
	std::deque<Intersection> xs = r.intersect(s);

	EXPECT_EQ(xs.size(), 2);
	EXPECT_EQ(xs[0].t, 3);
	EXPECT_EQ(xs[1].t, 7);
}

TEST(RayTest, TranslatedSphereIntersection) {
	Sphere s;
	Ray r(point(0, 0, -5), vec(0, 0, 1));
	s.transform(translation(5, 0, 0));
	std::deque<Intersection> xs = r.intersect(s);

	EXPECT_EQ(xs.size(), 0);
}