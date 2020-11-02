#include "pch.h"

TEST(TupleTest, IsPoint) {

	Tuple p(4.3, -4.2, 3.1, 1.0);
	ASSERT_EQ(p.x, 4.3);
	ASSERT_EQ(p.y, -4.2);
	ASSERT_EQ(p.z, 3.1);
	ASSERT_TRUE(p.isAPoint());
	ASSERT_TRUE(!p.isAVector());
}

TEST(TupleTest, IsVector) {

	Tuple v(4.3, -4.2, 3.1, 0.0);
	ASSERT_EQ(v.x, 4.3);
	ASSERT_EQ(v.y, -4.2);
	ASSERT_EQ(v.z, 3.1);
	ASSERT_TRUE(!v.isAPoint());
	ASSERT_TRUE(v.isAVector());
}

TEST(TupleTest, FactoryPoint) {
	Tuple p = point(1, 2, 3);

	ASSERT_EQ(p.w, 1.0);
	ASSERT_EQ(p.x, 1);
	ASSERT_EQ(p.y, 2);
	ASSERT_EQ(p.z, 3);

}

TEST(TupleTest, FactoryVector) {
	Tuple p = vec(1, 2, 3);

	ASSERT_EQ(p.w, 0.0);
	ASSERT_EQ(p.x, 1);
	ASSERT_EQ(p.y, 2);
	ASSERT_EQ(p.z, 3);
}

TEST(TupleTest, Equality) {
	Tuple t1(2.3, 1, -5, 1);
	Tuple t2(2.3, 1, -5, 1);

	EXPECT_TRUE(t1 == t2);
}

TEST(TupleTest, Inequality) {
	Tuple t1(2.3, 1, -5, 1);
	Tuple t2(2.3, 2, -5, 1);

	EXPECT_FALSE(t1 == t2);
}

TEST(TupleTest, Addition) {
	Tuple t1(-4, 2, 1, 1);
	Tuple t2(2.3, -3.1, 0, 0);
	Tuple result(-1.7, -1.1, 1, 1);

	t1 = t1 + t2;

	EXPECT_TRUE(t1 == result);
	EXPECT_TRUE(t1.isAPoint());

}

TEST(TupleTest, PointsSubtraction) {
	Tuple t1(3.3, 2.0, -1, 1);
	Tuple t2(1.0, 1.0, 2.5, 1);
	Tuple result(2.3, 1.0, -3.5, 0);

	t1 = t1 - t2;

	EXPECT_TRUE(t1 == result);
	EXPECT_TRUE(t1.isAVector());
}

TEST(TupleTest, VectorAndPointSubtraction) {
	Tuple p(4.2, 1.0, -2.3, 1);
	Tuple v(1.0, 2.0, 1.0, 0);
	Tuple result(3.2, -1.0, -3.3, 1);

	p = p - v;

	EXPECT_TRUE(p == result);
	EXPECT_TRUE(p.isAPoint());

}

TEST(TupleTest, VectorsSubtraction) {
	Tuple v1(4.2, 1.0, -2.3, 0);
	Tuple v2(1.0, 2.0, 1.0, 0);
	Tuple result(3.2, -1.0, -3.3, 0);

	v1 = v1 - v2;

	EXPECT_TRUE(v1 == result);
	EXPECT_TRUE(v1.isAVector());
}

TEST(TupleTest, Negate) {
	Tuple t(1, 0, 3, -2);
	Tuple result(-1, 0, -3, 2);

	t = -t;

	EXPECT_TRUE(t == result);
}

TEST(TupleTest, Scale) {
	Tuple t(1.5, 2, 3, 0);
	Tuple result(3, 4, 6, 0);
	
	t = t * 2;

	EXPECT_TRUE(t == result);
}

TEST(TupleTest, Division) {
	Tuple result(1.5, 2, 3, 0);
	Tuple t(3, 4, 6, 0);

	t = t / 2;

	EXPECT_TRUE(t == result);
}