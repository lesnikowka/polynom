#include <gtest.h>
#include "Polynom.h"

class Fixture_Polynom : public ::testing::Test {
protected:
	Polynom<3, 5> p, p1, p2, p3;
};

TEST_F(Fixture_Polynom, get_str_is_correct) {
	p.parse("-1.23x0^2x2^1x1^0");

	EXPECT_EQ(p.get_str(), "-1.23x0^2x2^1");
}

//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )
//TEST_F(Fixture_Polinom, )