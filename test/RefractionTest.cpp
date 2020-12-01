#include "pch.h"

TEST(RefractionTest, MaterialProp) {
	Material m;
	EXPECT_EQ(m.transparency(), 0);
	EXPECT_EQ(m.refractiveIndex(), 1);
}

TEST(RefractionTest, GlassSphere) {
	Sphere s = glassSphere(1.5);
	EXPECT_TRUE(s.transform() == identity());
	EXPECT_EQ(s.material().transparency(), 1.0);
	EXPECT_EQ(s.material().refractiveIndex(), 1.5);
}

TEST(RefractionTest, IndicesOfRefraction) {
	Sphere s1 = glassSphere(1.5);
	s1.transform(scale(2, 2, 2));
	Sphere s2 = glassSphere(2.0);
	s2.transform(translation(0, 0, -0.25));
	Sphere s3 = glassSphere(2.5);
	s3.transform(translation(0, 0, 0.25));


	std::vector<Intersection> intx;
	intx.push_back(Intersection(2, &s1));
	intx.push_back(Intersection(2.75, &s2));
	intx.push_back(Intersection(3.25, &s3));
	intx.push_back(Intersection(4.75, &s2));
	intx.push_back(Intersection(5.25, &s3));
	intx.push_back(Intersection(6, &s1));

	// set up for intersection obj's
	Ray r(point(0, 0, -4), vec(0, 0, 1));
	double ns[] = { 1, 1.5, 1.5, 2.0, 2.0, 2.5, 2.5, 2.5, 2.5, 1.5, 1.5, 1.0 };

	for (int i = 0; i < 6; i++) {
		IntersectInfo xInfo(intx[i], r, intx);
		EXPECT_EQ(xInfo.n1, ns[2 * i]);
		EXPECT_EQ(xInfo.n2, ns[2 * i + 1]);
	}
}

TEST(RefractionTest, UnderPoint) {
	Ray r(point(0, 0, -5), vec(0, 0, 1));
	Sphere s = glassSphere(1.5);
	s.transform(translation(0, 0, 1));
	Intersection i(5, &s);
	std::vector<Intersection> intx;
	intx.push_back(i);
	IntersectInfo iInfo(i, r, intx);
	EXPECT_TRUE(iInfo.underPoint.z > Epsilon / 2);
	EXPECT_TRUE(iInfo.point.z < iInfo.underPoint.z);
}

TEST(RefractionTest, OpaqueObject) {
	World w = defaultWorld();
	Ray r(point(0, 0, -5), vec(0, 0, 1));
	Object* o = w.objects().front();
	std::vector<Intersection> intx;
	intx.push_back(Intersection(4, o));
	intx.push_back(Intersection(6, o));

	IntersectInfo iInf(intx[0], r, intx);
	Color c = refractedColor(w, iInf);
	EXPECT_TRUE(c == Color(0, 0, 0));
}

TEST(RefractionTest, MaximumRecursiveDepth) {
	World w;
	Sphere s = glassSphere(1.5);
	w.addObject(s);
	Ray r(point(0, 0, -5), vec(0, 0, 1));
	Object* o = w.objects().front();
	std::vector<Intersection> intx;
	intx.push_back(Intersection(4, o));
	intx.push_back(Intersection(6, o));

	IntersectInfo iInf(intx[0], r, intx);
	Color c = refractedColor(w, iInf, 0);
	EXPECT_TRUE(c == Color(0, 0, 0));
}

TEST(RefractionTest, RefractedRay) {
	World w = defaultWorld();
	Material a;
	a.ambient(1);
	a.pattern(testPattern());
	Material b;
	b.transparency(1);
	b.refractiveIndex(1.5);
	w.objects().front()->material(a);
	w.objects().back()->material(b);

	Ray r(point(0, 0, 0.1), vec(0, 1, 0));
	Object* o1 = w.objects().front();
	Object* o2 = w.objects().back();
	std::vector<Intersection> intx;
	intx.push_back(Intersection(-0.9899, o1));
	intx.push_back(Intersection(-0.4899, o2));
	intx.push_back(Intersection(0.4899, o2));
	intx.push_back(Intersection(0.9899, o1));

	IntersectInfo iInf(intx[2], r, intx);
	Color c = refractedColor(w, iInf);
	EXPECT_TRUE(c == Color(0, 0.99887, 0.04722));
}

TEST(RefractionTest, ShadeHit) {
	World w = defaultWorld();
	Plane floor;
	floor.transform(translation(0, -1, 0));
	Material mFloor;
	mFloor.transparency(0.5);
	mFloor.refractiveIndex(1.5);
	floor.material(mFloor);
	w.addObject(floor);
	Sphere ball;
	Material mBall;
	mBall.color(Color(1, 0, 0));
	mBall.ambient(0.5);
	ball.transform(translation(0, -3.5, -0.5));
	ball.material(mBall);
	w.addObject(ball);

	Ray r(point(0, 0, -3), vec(0, -sqrt(2) / 2, sqrt(2) / 2));
	Intersection i(sqrt(2), &floor);
	std::vector<Intersection> intx;
	intx.push_back(i);
	IntersectInfo iInf(intx[0], r, intx);
	Color c = shadeHit(w, iInf, 5);
	EXPECT_TRUE(c == Color(0.93642, 0.68642, 0.68642));
}

TEST(RefractionTest, FresnelTIR) {
	Sphere s = glassSphere(1.5);
	Ray r(point(0, 0, sqrt(2) / 2), vec(0, 1, 0));
	std::vector<Intersection> intx;
	intx.push_back(Intersection(-sqrt(2) / 2, &s));
	intx.push_back(Intersection(sqrt(2) / 2, &s));
	IntersectInfo iInf(intx[1], r, intx);
	double reflectance = fresnel(iInf);

	EXPECT_TRUE(doubleEqual(reflectance, 1.0));
}

TEST(RefractionTest, FresnelPerpindicular) {
	Sphere s = glassSphere(1.5);
	Ray r(point(0, 0, 0), vec(0, 1, 0));
	std::vector<Intersection> intx;
	intx.push_back(Intersection(-1, &s));
	intx.push_back(Intersection(1, &s));
	IntersectInfo iInf(intx[1], r, intx);
	double reflectance = fresnel(iInf);

	EXPECT_TRUE(doubleEqual(reflectance, 0.04));
}

TEST(RefractionTest, FresnelSmallAngle) {
	Sphere s = glassSphere(1.5);
	Ray r(point(0, 0.99, -2), vec(0, 0, 1));
	std::vector<Intersection> intx;
	intx.push_back(Intersection(1.8589, &s));
	IntersectInfo iInf(intx[0], r, intx);
	double reflectance = fresnel(iInf);

	EXPECT_TRUE(doubleEqual(reflectance, 0.48873));
}

TEST(RefractionTest, ShadeHitFresnel) {
	World w = defaultWorld();
	Plane floor;
	floor.transform(translation(0, -1, 0));
	Material mFloor;
	mFloor.reflective(0.5);
	mFloor.transparency(0.5);
	mFloor.refractiveIndex(1.5);
	floor.material(mFloor);
	w.addObject(floor);
	Sphere ball;
	Material mBall;
	mBall.color(Color(1, 0, 0));
	mBall.ambient(0.5);
	ball.transform(translation(0, -3.5, -0.5));
	ball.material(mBall);
	w.addObject(ball);

	Ray r(point(0, 0, -3), vec(0, -sqrt(2) / 2, sqrt(2) / 2));
	Intersection i(sqrt(2), &floor);
	std::vector<Intersection> intx;
	intx.push_back(i);
	IntersectInfo iInf(intx[0], r, intx);
	Color c = shadeHit(w, iInf, 5);
	EXPECT_TRUE(c == Color(0.93391, 0.69643, 0.69243));
}


