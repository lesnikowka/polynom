#include <gtest.h>
#include "Polynom.h"

class Fixture_Polynom : public ::testing::Test {
protected:
	Polynom<3, 5> p, p1, p2, p3;
};

TEST_F(Fixture_Polynom, get_str_is_correct) {
	p.parse("-1.23x0^2x2^1x1^0+2x2^2x1^2");

	EXPECT_EQ(p.get_str(), "2x1^2x2^2-1.23x0^2x2^1");
}

//"-1.23x0^2x2^1x1^0+2x2^2x1^2"



TEST_F(Fixture_Polynom, can_assign_polynom) {
	p1.parse("-1.23x0^2x2^1x1^0+2x2^2x1^2");

	p2 = p1;

	EXPECT_EQ(p1, p2);
}

TEST_F(Fixture_Polynom, can_copy_polynom) {
	p.parse("-1.23x0^2x2^1x1^0+2x2^2x1^2");
	
	Polynom<3,5> p4 = p;

	EXPECT_EQ(p, p4);
}

TEST_F(Fixture_Polynom, can_add_polynom) {
	p1.parse("-1.23x0^2x2^1x1^0+2x2^2x1^2");
	p2.parse("1.23x2^1x0^2+x0^2x1^2x2^2");
	
	p1 += p2;


	EXPECT_EQ(p1.get_str(), "2x1^2x2^2+x0^2x1^2x2^2");
}


TEST_F(Fixture_Polynom, can_sub_polynom) {
	p1.parse("-1.23x0^2x2^1x1^0+2x2^2x1^2");
	p2.parse("1.23x2^1x0^2+x0^2x1^2x2^2");

	p1 -= p2;


	EXPECT_EQ(p1.get_str(), "2x1^2x2^2-2.46x0^2x2^1-x0^2x1^2x2^2");
}

//TEST_F(Fixture_Polynom, ) 
//TEST_F(Fixture_Polynom, ) 
//TEST_F(Fixture_Polynom, ) 
//TEST_F(Fixture_Polynom, ) 
//TEST_F(Fixture_Polynom, ) 
//TEST_F(Fixture_Polynom, ) 
//TEST_F(Fixture_Polynom, ) 
//TEST_F(Fixture_Polynom, ) 
//TEST_F(Fixture_Polynom, ) 
//TEST_F(Fixture_Polynom, ) 
//TEST_F(Fixture_Polynom, ) 
//TEST_F(Fixture_Polynom, ) 
//TEST_F(Fixture_Polynom, ) 
//TEST_F(Fixture_Polynom, ) 
//TEST_F(Fixture_Polynom, ) 