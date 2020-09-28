#include "pch.h"
#include "../Raytracer/World.h"
#include "../Raytracer/World.cpp"

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
	EXPECT_TRUE(l1 == *l2);

}