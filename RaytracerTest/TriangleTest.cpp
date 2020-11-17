#include "pch.h"
#include <vector>

class TriangleTest : public ::testing::Test {
protected:
	void SetUp() override {
		t = Triangle(point(0, 1, 0), point(-1, 0, 0), point(1, 0, 0));
	}

	Triangle t;
};

class SmoothTriangleTest : public ::testing::Test {
protected:
	void SetUp() override {
		t = SmoothTriangle(point(0, 1, 0), point(-1, 0, 0), point(1, 0, 0),
			vec(0, 1, 0), vec(-1, 0, 0), vec(1, 0, 0));
	}
	SmoothTriangle t;
};

TEST_F(TriangleTest, Constructor) {
	Tuple p1 = point(0, 1, 0);
	Tuple p2 = point(-1, 0, 0);
	Tuple p3 = point(1, 0, 0);

	EXPECT_TRUE(t.p1() == p1);
	EXPECT_TRUE(t.p2() == p2);
	EXPECT_TRUE(t.p3() == p3);
	EXPECT_TRUE(t.e1() == vec(-1, -1, 0));
	EXPECT_TRUE(t.e2() == vec(1, -1, 0));
	EXPECT_TRUE(t.normal() == vec(0, 0, -1));

}

TEST_F(TriangleTest, Normal) {

	Tuple n1 = t.normalAt(point(0, 0.5, 0), Intersection(0, &t));
	Tuple n2 = t.normalAt(point(-0.5, 0.75, 0), Intersection(0, &t));
	Tuple n3 = t.normalAt(point(0.5, 0.25, 0), Intersection(0, &t));

	EXPECT_TRUE(t.normal() == n1);
	EXPECT_TRUE(t.normal() == n2);
	EXPECT_TRUE(t.normal() == n3);

}




TEST_F(TriangleTest, MissCoplanar) {
	Ray r(point(0, -1, -2), vec(0, 1, 0));
	std::vector<Intersection> intx;
	t.localIntersect(r, intx);
	EXPECT_EQ(intx.size(), 0);
}

TEST_F(TriangleTest, MissP1P3) {
	Ray r(point(1, 1, -2), vec(0, 0, 1));
	std::vector<Intersection> intx;
	t.localIntersect(r, intx);
	EXPECT_EQ(intx.size(), 0);
}

TEST_F(TriangleTest, MissP1P2) {
	Ray r(point(-1, 1, -2), vec(0, 0, 1));
	std::vector<Intersection> intx;
	t.localIntersect(r, intx);
	EXPECT_EQ(intx.size(), 0);
}

TEST_F(TriangleTest, MissP2P3) {
	Ray r(point(0, -1, -2), vec(0, 0, 1));
	std::vector<Intersection> intx;
	t.localIntersect(r, intx);
	EXPECT_EQ(intx.size(), 0);
}

TEST_F(TriangleTest, Hit) {
	Ray r(point(0, 0.5, -2), vec(0, 0, 1));
	std::vector<Intersection> intx;
	t.localIntersect(r, intx);
	EXPECT_EQ(intx.size(), 1);
	EXPECT_EQ(intx[0].t, 2);
}

TEST(ParserTest, Gibberish) {
	ObjParser parser;
	parser.parse("../RaytracerTest/files/parseGibberish.txt");
	EXPECT_EQ(parser.ignoredLines(), 7);
}

TEST(ParserTest, Vertices) {
	ObjParser parser;
	parser.parse("../RaytracerTest/files/parseVertices.txt");
	std::vector<Tuple> vertices = parser.vertices();
	EXPECT_TRUE(vertices[0] == point(-1, 1, 0));
	EXPECT_TRUE(vertices[1] == point(-1, 0.5, 0));
	EXPECT_TRUE(vertices[2] == point(1, 0, 0));
	EXPECT_TRUE(vertices[3] == point(1, 1, 0));
}

TEST(ParserTest, Triangles) {
	ObjParser parser;
	parser.parse("../RaytracerTest/files/parseTriangles.txt");
	std::vector<Tuple> vertices = parser.vertices();
	std::vector<Triangle> triangles = parser.faces();

	EXPECT_TRUE(triangles[0].p1() == vertices[0]);
	EXPECT_TRUE(triangles[0].p2() == vertices[1]);
	EXPECT_TRUE(triangles[0].p3() == vertices[2]);

	EXPECT_TRUE(triangles[1].p1() == vertices[0]);
	EXPECT_TRUE(triangles[1].p2() == vertices[2]);
	EXPECT_TRUE(triangles[1].p3() == vertices[3]);

}

TEST(ParserTest, Triangulate) {
	ObjParser parser;
	parser.parse("../RaytracerTest/files/parseTriangulate.txt");
	std::vector<std::pair<std::string, Group>> grps = parser.groups();
	Group g = grps[0].second;
	std::vector<Tuple> vertices = parser.vertices();
	std::vector<Triangle> triangles = parser.faces();

	EXPECT_TRUE(triangles[0].p1() == vertices[0]);
	EXPECT_TRUE(triangles[0].p2() == vertices[1]);
	EXPECT_TRUE(triangles[0].p3() == vertices[2]);

	EXPECT_TRUE(triangles[1].p1() == vertices[0]);
	EXPECT_TRUE(triangles[1].p2() == vertices[2]);
	EXPECT_TRUE(triangles[1].p3() == vertices[3]);

	EXPECT_TRUE(triangles[2].p1() == vertices[0]);
	EXPECT_TRUE(triangles[2].p2() == vertices[3]);
	EXPECT_TRUE(triangles[2].p3() == vertices[4]);

}

TEST(ParserTest, TrianglesGroups) {
	ObjParser parser;
	parser.parse("../RaytracerTest/files/parseGroups.txt");
	std::vector<std::pair<std::string, Group>> grps = parser.groups();
	Group g1 = grps[1].second;
	Group g2 = grps[2].second;
	Object* t1 = g1.children()[0];
	Object* t2 = g2.children()[0];
	std::vector<Tuple> vertices = parser.vertices();
	std::vector<Triangle> triangles = parser.faces();

	EXPECT_EQ(g1.children().size(), 1);
	EXPECT_EQ(g2.children().size(), 1);

}

TEST(ParserTest, GroupOutput) {
	ObjParser parser;
	parser.parse("../RaytracerTest/files/parseGroups.txt");
	Group output = parser.objToGroup();
	std::vector<std::pair<std::string, Group>> grps = parser.groups();
	Group g1 = grps[1].second;
	Group g2 = grps[2].second;
	Object* t1 = g1.children()[0];
	Object* t2 = g2.children()[0];

	Ray r(point(0, 0, -5), vec(0, 0, 1));
	std::vector<Intersection> intx;
	output.localIntersect(r, intx);

}

TEST_F(SmoothTriangleTest, Constructor) {
	EXPECT_TRUE(t.p1() == point(0, 1, 0));
	EXPECT_TRUE(t.p2() == point(-1, 0, 0));
	EXPECT_TRUE(t.p3() == point(1, 0, 0));
	EXPECT_TRUE(t.n1() == vec(0, 1, 0));
	EXPECT_TRUE(t.n2() == vec(-1, 0, 0));
	EXPECT_TRUE(t.n3() == vec(1, 0, 0));
}


TEST_F(SmoothTriangleTest, IntersectionUV) {
	Object* o = &Triangle();
	Intersection i = intersectionWithUV(3.5, o, 0.2, 0.4);
	EXPECT_TRUE(doubleEqual(i.u, 0.2));
	EXPECT_TRUE(doubleEqual(i.v, 0.4));
}

TEST_F(SmoothTriangleTest, IntersectionWithTriangle) {
	Ray r(point(-0.2, 0.3, -2), vec(0, 0, 1));
	std::vector<Intersection> intx;
	t.localIntersect(r, intx);

	EXPECT_TRUE(doubleEqual(intx[0].u, 0.45));
	EXPECT_TRUE(doubleEqual(intx[0].v, 0.25));
}

TEST_F(SmoothTriangleTest, NormalInterpolation) {
	Intersection i = intersectionWithUV(1, &t, 0.45, 0.25);
	Tuple n = normalAt(point(0, 0, 0), t, i);
	EXPECT_TRUE(n == vec(-0.5547, 0.83205, 0));
}

TEST_F(SmoothTriangleTest, PreparingNormal) {
	Intersection i = intersectionWithUV(1, &t, 0.45, 0.25);
	Ray r(point(-0.2, 0.3, -2), vec(0, 0, 1));
	std::vector<Intersection> intx;
	intx.push_back(i);
	IntersectInfo iInf(i, r, intx);
	EXPECT_TRUE(iInf.normalv == vec(-0.5547, 0.83205, 0));
}

TEST(ParserTest, VertexNormals) {
	ObjParser parser;
	parser.parse("../RaytracerTest/files/parseVN.txt");
	std::vector<Tuple> norms = parser.normals();
	EXPECT_TRUE(norms[0] == vec(0, 0, 1));
	EXPECT_TRUE(norms[1] == vec(0.707, 0, -0.707));
	EXPECT_TRUE(norms[2] == vec(1, 2, 3));
}

TEST(ParserTest, VertexFaceNormals) {
	ObjParser parser;
	parser.parse("../RaytracerTest/files/parseFaceVN.txt");
	std::vector<Tuple> norms = parser.normals();
	std::vector<Tuple> verts = parser.vertices();
	std::vector<SmoothTriangle> tris = parser.smoothFaces(); //smooth

	EXPECT_TRUE(tris[0].p1() == verts[0]);
	EXPECT_TRUE(tris[0].p2() == verts[1]);
	EXPECT_TRUE(tris[0].p3() == verts[2]);
	
	EXPECT_TRUE(tris[0].n1() == norms[2]);
	EXPECT_TRUE(tris[0].n2() == norms[0]);
	EXPECT_TRUE(tris[0].n3() == norms[1]);
}