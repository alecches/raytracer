#include "pch.h"
#include "../Raytracer/Tuple.h"

using namespace std;


TEST(TupleTest, IsAPoint) {
	
	Tuple p(4.3, -4.2, 3.1, 1.0);
	ASSERT_EQ(p.x, 4.3);
	ASSERT_EQ(p.y, -4.2);
	ASSERT_EQ(p.z, -3.1);
	ASSERT_TRUE(p.isAPoint());
	ASSERT_TRUE(!p.isAVector());
}

TEST(TupleTest, IsAVector) {
	
	Tuple v(4.3, -4.2, 3.1, 1.0);
	ASSERT_EQ(v.x, 4.3);
	ASSERT_EQ(v.y, -4.2);
	ASSERT_EQ(v.z, -3.1);
	ASSERT_TRUE(!v.isAPoint());
	ASSERT_TRUE(v.isAVector());
}