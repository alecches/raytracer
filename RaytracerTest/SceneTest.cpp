#include "pch.h"
#include "../Raytracer/World.h"
#include "../Raytracer/Camera.h"
#include "../Raytracer/Camera.cpp"
#include "../Raytracer/Util.h"
#include "../Raytracer/World.cpp"
#include "../Raytracer/Canvas.h"


TEST(SceneTest, WorldConstructor) {
	World w = World();

	EXPECT_EQ(w.lights().size(), 0);
	EXPECT_EQ(w.objects().size(), 0);
}

TEST(SceneTest, DefaultWorld) {
	World w = defaultWorld();
	PointLight l1 = PointLight(point(-10, 10, -10), Color(1, 1, 1));
	Sphere s1 = Sphere();
	Material m1 = Material();
	m1.color(Color(0.8, 1, 0.6));
	m1.diffuse(0.7);
	m1.specular(0.2);
	s1.material(m1);
	Sphere s2 = Sphere();
	s2.transform(scale(0.5, 0.5, 0.5));

	Light* l2 = w.lights().front();
	EXPECT_TRUE(&l1 == l2);

}

TEST(SceneTest, IntersectWorld) {
	World w = defaultWorld();
	Ray r = Ray(point(0, 0, -5), vec(0, 0, 1));
	std::deque<Intersection> intx = intersect(r, w);

	EXPECT_EQ(intx.size(), 4);
	EXPECT_EQ(intx[0].t, 4);
	EXPECT_EQ(intx[1].t, 4.5);
	EXPECT_EQ(intx[2].t, 5.5);
	EXPECT_EQ(intx[3].t, 6);
}

TEST(SceneTest, IntersectionState) {
	Ray r = Ray(point(0, 0, -5), vec(0, 0, 1));
	Sphere s = Sphere();
	Intersection i = Intersection(4, s);

	IntersectInfo preComps = IntersectInfo(i, r);

	EXPECT_EQ(preComps.t, i.t);
	EXPECT_TRUE(&preComps.object == &i.object);
	EXPECT_TRUE(preComps.point == point(0, 0, -1));
	EXPECT_TRUE(preComps.eyev == vec(0, 0, -1));
	EXPECT_TRUE(preComps.normalv == vec(0, 0, -1));
	EXPECT_FALSE(preComps.inside);

}

TEST(SceneTest, IntersectionStateInside) {
	Ray r = Ray(point(0, 0, 0), vec(0, 0, 1));
	Sphere s = Sphere();
	Intersection i = Intersection(1, s);

	IntersectInfo preComps = IntersectInfo(i, r);

	EXPECT_EQ(preComps.t, i.t);
	EXPECT_TRUE(&preComps.object == &i.object);
	EXPECT_TRUE(preComps.point == point(0, 0, 1));
	EXPECT_TRUE(preComps.eyev == vec(0, 0, -1));
	EXPECT_TRUE(preComps.normalv == vec(0, 0, -1));
	EXPECT_TRUE(preComps.inside);

}

TEST(SceneTest, ShadeIntersection) {
	World w = defaultWorld();
	Ray r = Ray(point(0, 0, -5), vec(0, 0, 1));
	Object* o = w.objects().front();
	Intersection i = Intersection(4, *o);
	IntersectInfo iInf = IntersectInfo(i, r);
	Color c = shadeHit(w, iInf);

	EXPECT_TRUE(c == Color(0.38066, 0.47583, 0.2855));
}

TEST(SceneTest, ShadeIntersectionInside) {
	
	World w = defaultWorld(PointLight(point(0, 0.25, 0), Color(1, 1, 1)));
	Ray r = Ray(point(0, 0, 0), vec(0, 0, 1));
	Object* o = w.objects().back();
	Intersection i = Intersection(0.5, *o);
	IntersectInfo iInf = IntersectInfo(i, r);
	Color c = shadeHit(w, iInf);

	EXPECT_TRUE(c == Color(0.90498, 0.90498, 0.90498));
}

TEST(SceneTest, RayMisses) {
	World w = defaultWorld();
	Ray r(point(0, 0, -5), vec(0, 1, 0));
	Color c = colorAt(w, r);

	EXPECT_TRUE(c == Color(0, 0, 0));
}

TEST(SceneTest, RayHits) {
	World w = defaultWorld();
	Ray r(point(0, 0, -5), vec(0, 0, 1));
	Color c = colorAt(w, r);

	EXPECT_TRUE(c == Color(0.38066, 0.47583, 0.2855));
}

TEST(SceneTest, RayHitsInner) {

	PointLight l = PointLight(point(-10, 10, -10), Color(1, 1, 1));
	Sphere s1 = Sphere();
	Material m1;
	Material m2;
	m1.color(Color(0.8, 1, 0.6));
	m1.diffuse(0.7);
	m1.specular(0.2);
	m1.ambient(1); //differs from default...
	m2.ambient(1);
	s1.material(m1);
	Sphere s2 = Sphere();
	s2.transform(scale(0.5, 0.5, 0.5));
	s2.material(m2);

	World w;
	w.addLight(l);
	w.addObject(s1);
	w.addObject(s2);

	Ray r(point(0, 0, 0.75), vec(0, 0, -1));
	Color c = colorAt(w, r);
	EXPECT_TRUE(c == s2.material().color());
	
}

TEST(SceneTest, ViewStandard) {
	Tuple from = point(0, 0, 0);
	Tuple to = point(0, 0, -1);
	Tuple up = vec(0, 1, 0);

	Matrix t = view(from, to, up);
	EXPECT_TRUE(t == identity());
}

TEST(SceneTest, ViewFlipped) {
	Tuple from = point(0, 0, 0);
	Tuple to = point(0, 0, 1);
	Tuple up = vec(0, 1, 0);

	Matrix t = view(from, to, up);
	EXPECT_TRUE(t == scale(-1, 1, -1));
}

TEST(SceneTest, ViewMovesWorld) {
	Tuple from = point(0, 0, 8);
	Tuple to = point(0, 0, 0);
	Tuple up = vec(0, 1, 0);

	Matrix t = view(from, to, up);
	EXPECT_TRUE(t == translation(0, 0, -8));
}

TEST(SceneTest, ViewArbitrary) {
	Tuple from = point(1, 3, 2);
	Tuple to = point(4, -2, 8);
	Tuple up = vec(1, 1, 0);

	Matrix m;
	m <<
		-0.50709, 0.50709, 0.67612, -2.36643,
		0.76772, 0.60609, 0.12122, -2.82843,
		-0.35857, 0.59761, -0.71714, 0,
		0, 0, 0, 1;

	Matrix t = view(from, to, up);
	EXPECT_TRUE(t == m);
}

TEST(SceneTest, CameraConstructor) {
	Camera c(160, 120, PI / 2);

	EXPECT_EQ(c.hsize(), 160);
	EXPECT_EQ(c.vsize(), 120);
	EXPECT_EQ(c.fov(), PI / 2);
	EXPECT_TRUE(c.transform() == identity());
}

TEST(SceneTest, CameraPixelVert) {
	Camera c(125, 200, PI / 2);
	EXPECT_TRUE(doubleEqual(c.pixelSize(), 0.01));
}

TEST(SceneTest, CameraPixelHoriz) {
	Camera c(200, 125, PI / 2);
	EXPECT_TRUE(doubleEqual(c.pixelSize(), 0.01));
}

TEST(SceneTest, RayThroughCenter) {
	Camera c(201, 101, PI / 2);
	Ray r = c.rayForPixel(100, 50);
	EXPECT_TRUE(r.origin() == point(0, 0, 0));
	EXPECT_TRUE(r.direction() == vec(0, 0, -1));
}

TEST(SceneTest, RayThroughCorner) {
	Camera c(201, 101, PI / 2);
	Ray r = c.rayForPixel(0, 0);
	EXPECT_TRUE(r.origin() == point(0, 0, 0));
	EXPECT_TRUE(r.direction() == vec(0.66519, 0.33259, -0.66851));
}

TEST(SceneTest, RayTransformedCam) {
	Camera c(201, 101, PI / 2);	
	c.transform(rotationY(PI / 4) * translation(0, -2, 5));
	Ray r = c.rayForPixel(100, 50);
	EXPECT_TRUE(r.origin() == point(0, 2, -5));
	EXPECT_TRUE(r.direction() == vec(sqrt(2)/2, 0, -sqrt(2)/2));
}

TEST(SceneTest, RenderWorld) {
	World w = defaultWorld();
	Camera c(11, 11, PI / 2);
	Tuple from = point(0, 0, -5);
	Tuple to = point(0, 0, 0);
	Tuple up = vec(0, 1, 0);
	c.transform(view(from, to, up));

	Canvas image = render(c, w);
	EXPECT_TRUE(image.getPixel(5, 5) == Color(0.38066, 0.47583, 0.2855));
}