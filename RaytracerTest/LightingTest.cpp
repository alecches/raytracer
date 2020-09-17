#include "pch.h"
#include "../Raytracer/Sphere.h"
#include "../Raytracer/TupleFactory.h"
#include "../Raytracer/Util.h"
#include "../Raytracer/PointLight.h"
#include "../Raytracer/Material.h"
#include "../Raytracer/Material.cpp"

TEST(LightingTest, SphereNormX) {
	Sphere s;
	Tuple p = s.normalAt(point(1, 0, 0));

	EXPECT_TRUE(p == vec(1, 0, 0));
}

TEST(LightingTest, SphereNormY) {
	Sphere s;
	Tuple p = s.normalAt(point(0, 1, 0));

	EXPECT_TRUE(p == vec(0, 1, 0));
}

TEST(LightingTest, SphereNormZ) {
	Sphere s;
	Tuple p = s.normalAt(point(0, 0, 1));

	EXPECT_TRUE(p == vec(0, 0, 1));
}

TEST(LightingTest, SphereNormNonAxial) {
	Sphere s;
	Tuple p = s.normalAt(point(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3));

	EXPECT_TRUE(p == vec(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
}

TEST(LightingTest, SphereNormNormalized) {
	Sphere s;
	Tuple p = s.normalAt(point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));

	EXPECT_TRUE(p == p.normalize());
}

TEST(LightingTest, NormalTranslated) {
	Sphere s;
	s.transform(translation(0, 1, 0));
	Tuple n = s.normalAt(point(0, 1.70711, -0.70711));

	EXPECT_TRUE(n == vec(0, 0.70711, -0.70711));
}

TEST(LightingTest, NormalScaledRotated) {
	Sphere s;
	s.transform(scale(1, 0.5, 1) * rotationZ(PI/5));
	Tuple n = s.normalAt(point(0, sqrt(2)/2, -sqrt(2)/2));

	EXPECT_TRUE(n == vec(0, 0.97014, -0.24254));
}

TEST(LightingTest, Reflect) {
	Tuple v = vec(1, -1, 0);
	Tuple n = vec(0, 1, 0);
	Tuple r = v.reflect(n);

	EXPECT_TRUE(r == vec(1, 1, 0));
}

TEST(LightingTest, ReflectSlanted) {
	Tuple v = vec(0, -1, 0);
	Tuple n = vec(sqrt(2)/2, sqrt(2)/2, 0);
	Tuple r = v.reflect(n);

	EXPECT_TRUE(r == vec(1, 0, 0));
}

TEST(LightingTest, PointConstructor) {
	Color intensity(1, 1, 1);
	Tuple position = point(0, 0, 0);
	PointLight l(position, intensity);
	
	EXPECT_TRUE(l.intensity() == intensity);
	EXPECT_TRUE(l.position() == position);
}

TEST(LightingTest, MaterialConstructor) {
	Material m;

	EXPECT_TRUE(m.color() == Color(1, 1, 1));
	EXPECT_EQ(m.ambient(),0.1);
	EXPECT_EQ(m.diffuse(),0.9);
	EXPECT_EQ(m.specular(), 0.9);
	EXPECT_EQ(m.shininess(), 200);
}

TEST(LightingTest, SphereMaterial) {
	Sphere s;
	Material m = s.material();
	Material standard;
	//Material another;

	EXPECT_TRUE(m == Material());
}

TEST(LightingTest, SphereMatAssign) {
	Sphere s;
	Material m;
	m.ambient(1.0);
	s.material(m);

	EXPECT_TRUE(s.material() == m);

}

TEST(LightingTest, Lighting1) {
	Material m;
	Tuple position = point(0, 0, 0);
	Tuple eye = vec(0, 0, -1);
	Tuple normal = vec(0, 0, -1);
	PointLight light(point(0, 0, -10), Color(1, 1, 1));

	Color result = lighting(m, light, position, eye, normal);

	EXPECT_TRUE(result == Color(1.9, 1.9, 1.9));
}

TEST(LightingTest, Lighting2) {
	Material m;
	Tuple position = point(0, 0, 0);
	Tuple eye = vec(0, sqrt(2)/2, -sqrt(2)/2);
	Tuple normal = vec(0, 0, -1);
	PointLight light(point(0, 0, -10), Color(1, 1, 1));

	Color result = lighting(m, light, position, eye, normal);

	EXPECT_TRUE(result == Color(1, 1, 1));
}

TEST(LightingTest, Lighting3) {
	Material m;
	Tuple position = point(0, 0, 0);
	Tuple eye = vec(0, 0, -1);
	Tuple normal = vec(0, 0, -1);
	PointLight light(point(0, 10, -10), Color(1, 1, 1));

	Color result = lighting(m, light, position, eye, normal);

	EXPECT_TRUE(result == Color(0.7364, 0.7364, 0.7364));
}

TEST(LightingTest, Lighting4) {
	Material m;
	Tuple position = point(0, 0, 0);
	Tuple eye = vec(0, -sqrt(2) / 2, -sqrt(2) / 2);
	Tuple normal = vec(0, 0, -1);
	PointLight light(point(0, 10, -10), Color(1, 1, 1));

	Color result = lighting(m, light, position, eye, normal);

	EXPECT_TRUE(result == Color(1.6364, 1.6364, 1.6364));
}

TEST(LightingTest, Lighting5) {
	Material m;
	Tuple position = point(0, 0, 0);
	Tuple eye = vec(0, 0, -1);
	Tuple normal = vec(0, 0, -1);
	PointLight light(point(0, 0, 10), Color(1, 1, 1));

	Color result = lighting(m, light, position, eye, normal);

	EXPECT_TRUE(result == Color(0.1, 0.1, 0.1));
}

