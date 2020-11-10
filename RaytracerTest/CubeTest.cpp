#include "pch.h"

TEST(CubeTest, Intersect) {
	Cube c;
	std::vector<Ray> rays;
	rays.push_back(Ray(point(5, 0.5, 0), vec(-1, 0, 0)));
	rays.push_back(Ray(point(-5, 0.5, 0), vec(1, 0, 0)));
	rays.push_back(Ray(point(0.5, 5, 0), vec(0, -1, 0)));
	rays.push_back(Ray(point(0.5, -5, 0), vec(0, 1, 0)));
	rays.push_back(Ray(point(0.5, 0, 5), vec(0, 0, -1)));
	rays.push_back(Ray(point(0.5, 0, -5), vec(0, 0, 1)));
	rays.push_back(Ray(point(0, 0.5, 0), vec(0, 0, 1)));

	for (int i = 0; i < 7; i++) {
		std::vector<Intersection> intx;
		c.intersect(rays[i], intx);
		EXPECT_EQ(intx.size(), 2);
		if (i == 6) {
			EXPECT_EQ(intx[0].t, -1);
			EXPECT_EQ(intx[1].t, 1);
		}
		else {
			EXPECT_EQ(intx[0].t, 4);
			EXPECT_EQ(intx[1].t, 6);

		}
	}
}

TEST(CubeTest, Misses) {
	Cube c;
	std::vector<Ray> rays;
	rays.push_back(Ray(point(-2, 0, 0), vec(0.2673, 0.5345, 0.8018)));
	rays.push_back(Ray(point(0, -2, 0), vec(0.8018, 0.2673, 0.5345)));
	rays.push_back(Ray(point(0, 0, -2), vec(0.5345, 0.8018, 0.2673)));
	rays.push_back(Ray(point(2, 0, 2), vec(0, 0, -1)));
	rays.push_back(Ray(point(0, 2, 2), vec(0, -1, 0)));
	rays.push_back(Ray(point(2, 2, 0), vec(-1, 0, 0)));

	for (int i = 0; i < 6; i++) {
		std::vector<Intersection> intx;
		c.intersect(rays[i], intx);
		EXPECT_EQ(intx.size(), 0);
	}
}

TEST(CubeTest, Normals) {
	Cube c;
	Tuple points[8];
	Tuple normals[8];
	points[0] = point(1, 0.5, -0.8);
	points[1] = point(-1, -0.2, 0.9);
	points[2] = point(-0.4, 1, -0.1);
	points[3] = point(0.3, -1, -0.7);
	points[4] = point(-0.6, 0.3, 1);
	points[5] = point(0.4, 0.4, -1);
	points[6] = point(1, 1, 1);
	points[7] = point(-1, -1, -1);

	normals[0] = vec(1, 0, 0);
	normals[1] = vec(-1, 0, 0);
	normals[2] = vec(0, 1, 0);
	normals[3] = vec(0, -1, 0);
	normals[4] = vec(0, 0, 1);
	normals[5] = vec(0, 0, -1);
	normals[6] = vec(1, 0, 0);
	normals[7] = vec(-1, 0, 0);
}