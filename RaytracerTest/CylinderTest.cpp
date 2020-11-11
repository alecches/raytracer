#include "pch.h"

TEST(CylinderTest, Misses) {
	Cylinder cyl;
	std::vector<Ray> rays;
	rays.push_back(Ray(point(1, 0, 0), vec(0, 1, 0)));
	rays.push_back(Ray(point(0, 0, 0), vec(0, 1, 0)));
	rays.push_back(Ray(point(0, 0, -5), vec(1, 1, 1).normalize()));

	for (Ray r : rays) {
		std::vector<Intersection> intx;
		cyl.localIntersect(r, intx);
		EXPECT_EQ(intx.size(), 0);
	}
}

TEST(CylinderTest, Hits) {
	Cylinder cyl;
	std::vector<Ray> rays;
	rays.push_back(Ray(point(1, 0, -5), vec(0, 0, 1)));
	rays.push_back(Ray(point(0, 0, -5), vec(0, 0, 1)));
	rays.push_back(Ray(point(0.5, 0, -5), vec(0.1, 1, 1).normalize()));
	double ts[6] = {5, 5, 4, 6, 6.80798, 7.08872};

	int i = 0;
	for (Ray r : rays) {
		std::vector<Intersection> intx;
		cyl.localIntersect(r, intx);
		EXPECT_EQ(intx.size(), 2);
		EXPECT_TRUE(doubleEqual(intx[0].t, ts[i++]));
		EXPECT_TRUE(doubleEqual(intx[1].t, ts[i++]));
	}
}

TEST(CylinderTest, Normals) {
	Cylinder cyl;
	Tuple points[4];
	points[0] = point(1, 0, 0);
	points[1] = point(0, 5, -1);
	points[2] = point(0, -2, 1);
	points[3] = point(-1, 1, 0);
	Tuple normals[4];
	normals[0] = vec(1, 0, 0);
	normals[1] = vec(0, 0, -1);
	normals[2] = vec(0, 0, 1);
	normals[3] = vec(-1, 0, 0);

	for (int i = 0; i < 4;i++) {
		EXPECT_TRUE(cyl.normalAt(points[i]) == normals[i]);
	}
}

TEST(CylinderTest, DefaultLength) {
	Cylinder cyl;
	EXPECT_EQ(cyl.minimum(), std::numeric_limits<double>::lowest());
	EXPECT_EQ(cyl.maximum(), std::numeric_limits<double>::infinity());
}

TEST(CylinderTest, Truncated) {
	Cylinder cyl;
	cyl.minimum(1);
	cyl.maximum(2);
	std::vector<Ray> rays;
	rays.push_back(Ray(point(0, 1.5, 0), vec(0.1, 1, 0).normalize()));
	rays.push_back(Ray(point(0, 3, -5), vec(0, 0, 1).normalize()));
	rays.push_back(Ray(point(0, 0, -5), vec(0, 0, 1).normalize()));
	rays.push_back(Ray(point(0, 2, -5), vec(0, 0, 1).normalize()));
	rays.push_back(Ray(point(0, 1, -5), vec(0, 0, 1).normalize()));
	rays.push_back(Ray(point(0, 1.5, -5), vec(0, 0, 1).normalize()));


	int i = 0;
	for (Ray r : rays) {
		std::vector<Intersection> intx;
		cyl.localIntersect(r, intx);
		if (++i == 6) EXPECT_EQ(intx.size(), 2);
		else EXPECT_EQ(intx.size(), 0);
	}
}

TEST(CylinderTest, ClosedAttribute) {
	Cylinder cyl;
	EXPECT_FALSE(cyl.closed);
}

TEST(CylinderTest, ClosedIntersect) {
	Cylinder cyl;
	cyl.minimum(1);
	cyl.maximum(2);
	cyl.closed = true;
	std::vector<Ray> rays;
	rays.push_back(Ray(point(0, 3, 0), vec(0, -1, 0).normalize()));
	rays.push_back(Ray(point(0, 3, -2), vec(0, -1, 2).normalize()));
	rays.push_back(Ray(point(0, 4, -2), vec(0, -1, 1).normalize()));
	rays.push_back(Ray(point(0, 0, -2), vec(0, 1, 2).normalize()));
	rays.push_back(Ray(point(0, -1, -2), vec(0, 1, 1).normalize()));

	for (Ray r : rays) {
		std::vector<Intersection> intx;
		cyl.localIntersect(r, intx);
		EXPECT_EQ(intx.size(), 2);
	}
}

TEST(CylinderTest, ClosedNormals) {
	Cylinder cyl;
	cyl.closed = true;
	cyl.minimum(1);
	cyl.maximum(2);
	Tuple points[6];
	points[0] = point(0, 1, 0);
	points[1] = point(0.5, 1, 0);
	points[2] = point(0, 1, 0.5);
	points[3] = point(0, 2, 0);
	points[4] = point(0.5, 2, 0);
	points[5] = point(0, 2, 0.5);
	Tuple normals[6];
	normals[0] = vec(0, -1, 0);
	normals[1] = vec(0, -1, 0);
	normals[2] = vec(0, -1, 0);
	normals[3] = vec(0, 1, 0);
	normals[4] = vec(0, 1, 0);
	normals[5] = vec(0, 1, 0);

	for (int i = 0; i < 6;i++) {
		EXPECT_TRUE(cyl.normalAt(points[i]) == normals[i]);
	}
}

TEST(ConeTest, Intersect) {
	Cone c;
	std::vector<Ray> rays;
	rays.push_back(Ray(point(0, 0, -5), vec(0, 0, 1).normalize()));
	rays.push_back(Ray(point(0, 0, -5), vec(1, 1, 1).normalize()));
	rays.push_back(Ray(point(1, 1, -5), vec(-0.5, -1, 1).normalize()));
	double ts[6] = { 5, 5, 8.66025, 8.66025, 4.55006, 49.44994 };

	int i = 0;
	for (Ray r : rays) {
		std::vector<Intersection> intx;
		c.localIntersect(r, intx);
		EXPECT_EQ(intx.size(), 2);
		EXPECT_TRUE(doubleEqual(intx[0].t, ts[i++]));
		EXPECT_TRUE(doubleEqual(intx[1].t, ts[i++]));
	}
}

TEST(ConeTest, ParallelRay) {
	Cone c;
	Ray r(point(0, 0, -1), vec(0, 1, 1).normalize());
	std::vector<Intersection> intx;
	c.localIntersect(r, intx);
	EXPECT_EQ(intx.size(), 1);
	EXPECT_TRUE(doubleEqual(intx[0].t, 0.35355));
}

TEST(ConeTest, Caps) {
	Cone c;
	c.closed = true;
	c.maximum(0.5);
	c.minimum(-0.5);
	std::vector<Ray> rays;
	rays.push_back(Ray(point(0, 0, -5), vec(0, 1, 0).normalize()));
	rays.push_back(Ray(point(0, 0, -0.25), vec(0, 1, 1).normalize()));
	rays.push_back(Ray(point(0, 0, -0.25), vec(0, 1, 0).normalize()));
	double count[3] = { 0, 2, 4};

	int i = 0;
	for (Ray r : rays) {
		std::vector<Intersection> intx;
		c.localIntersect(r, intx);
		EXPECT_EQ(intx.size(), count[i++]);
	}
}

TEST(ConeTest, Normals) {
	Cone c;
	Tuple points[3];
	points[0] = point(0, 0, 0);
	points[1] = point(1, 1, 1);
	points[2] = point(-1, -1, 0);
	Tuple normals[3];
	normals[0] = vec(0, 0, 0);
	normals[1] = vec(1, -sqrt(2), 1);
	normals[2] = vec(-1, 1, 0);


	for (int i = 0; i < 3;i++) {
		EXPECT_TRUE(c.normalAt(points[i]) == normals[i]);
	}
}


