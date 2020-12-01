#include "pch.h"

TEST(ReflectionTest, MaterialAttrib) {
	Material m;
	EXPECT_EQ(m.reflective(), 0);
}

TEST(ReflectionTest, ReflectV) {
	Plane p;
	Ray r(point(0, 1, -1), vec(0, -sqrt(2) / 2, sqrt(2) / 2));
	Intersection i(sqrt(2), &p);
	IntersectInfo iInf(i, r);

	EXPECT_TRUE(iInf.reflectv == vec(0, sqrt(2) / 2, sqrt(2) / 2));
}

TEST(ReflectionTest, Nonreflective) {
	World w = defaultWorld();
	Ray r(point(0, 0, 0), vec(0, 0, 1));
	Material m;
	m.ambient(1);
	w.objects().back()->material(m);
	Object* obj = w.objects().back();
	Intersection i(1, obj);
	IntersectInfo iInf(i, r);
	Color refC = reflectedColor(w, iInf);
	EXPECT_TRUE(refC == Color(0, 0, 0));

}

TEST(ReflectionTest, Reflective) {
	World w = defaultWorld();

	// Put a reflective plane below the outer sphere
	Plane p;
	Material m;
	m.reflective(0.5);
	p.material(m);
	p.transform(translation(0, -1, 0));
	w.addObject(p);

	Ray r(point(0, 0, -3), vec(0, -sqrt(2) / 2, sqrt(2) / 2));
	Intersection i(sqrt(2), &p);
	IntersectInfo iInf(i, r);
	Color refC = reflectedColor(w, iInf);

	EXPECT_TRUE(refC == Color(0.19033, 0.23791, 0.14274));

}

TEST(ReflectionTest, SurfaceAndReflective) {
	World w = defaultWorld();

	// Put a reflective plane below the outer sphere
	Plane p;
	Material m;
	m.reflective(0.5);
	p.material(m);
	p.transform(translation(0, -1, 0));
	w.addObject(p);

	Ray r(point(0, 0, -3), vec(0, -sqrt(2) / 2, sqrt(2) / 2));
	Intersection i(sqrt(2), &p);
	IntersectInfo iInf(i, r);
	Color sumC = shadeHit(w, iInf);

	EXPECT_TRUE(sumC == Color(0.87675, 0.92434, 0.82917));

}

TEST(ReflectionTest, MutualReflection) {
	World w;
	w.addLight(PointLight(point(0, 0, 0), Color(1, 1, 1)));
	Plane lower;
	Material m;
	m.reflective(1);
	lower.material(m);
	lower.transform(translation(0, -1, 0));
	Plane upper;
	upper.material(m);
	upper.transform(translation(0, 1, 0));

	w.addObject(lower);
	w.addObject(upper);

	Ray r(point(0, 0, 0), vec(0, 1, 0));

	EXPECT_NO_THROW({ colorAt(w, r); });
	
}

TEST(ReflectionTest, LimitRecursion){
	World w = defaultWorld();

	// Put a reflective plane below the outer sphere
	Plane p;
	Material m;
	m.reflective(0.5);
	p.material(m);
	p.transform(translation(0, -1, 0));
	w.addObject(p);

	Ray r(point(0, 0, -3), vec(0, -sqrt(2) / 2, sqrt(2) / 2));
	Intersection i(sqrt(2), &p);
	IntersectInfo iInf(i, r);
	Color sumC = reflectedColor(w, iInf, 0);

	EXPECT_TRUE(sumC == Color(0, 0, 0));
}