#include <gtest.h>
#include "Monom.h"

class Fixture_Monom : public ::testing::Test {
protected:
	Monom<3, 5> m, m1, m2, m3;
};

TEST_F(Fixture_Monom, get_str_is_correct) {
	m.parse("-1.23x0^2x2^1x1^0");

	EXPECT_EQ(m.get_str(), "-1.23x0^2x2^1");
}

TEST_F(Fixture_Monom, get_deg_is_correct) {
	m.parse("-1.23x0^2x2^1x1^0");

	EXPECT_EQ(m.get_deg(), std::vector<size_t>({2,0,1}));
}


TEST_F(Fixture_Monom, get_coef_is_correct) {
	m.parse("-1.23x0^2x2^1x1^0");

	EXPECT_EQ(m.get_coef(), -1.23);
}


TEST_F(Fixture_Monom, can_calculate_monom) {
	m.parse("-2x0^2x1^2x2^1");

	EXPECT_EQ(m.calculate({ 2,3,3 }), -216);
}


TEST_F(Fixture_Monom, can_copy_monom) {
	m.parse("-2x0^2x1^2x2^1");

	Monom<3, 5> m4 = m;

	EXPECT_TRUE(m == m4);
}


TEST_F(Fixture_Monom, can_assign_monom) {
	m1.parse("-2x0^2x1^2x2^1");

	Monom<3, 5> m2 = m1;

	EXPECT_TRUE(m1 == m2);
}


TEST_F(Fixture_Monom, is_similar_is_correct_1) {
	m1.parse("-1.23x0^0x1^1x2^2");
	m2.parse("100x2^2x1^1");

	EXPECT_TRUE(m1.is_similar(m2));
}


TEST_F(Fixture_Monom, is_similar_is_correct_2) {
	m1.parse("-1.23x0^0x1^1x2^2");
	m3.parse("-1.23x0^0x1^1x2^1");

	EXPECT_FALSE(m1.is_similar(m3));
}

TEST_F(Fixture_Monom, false_if_degree_is_too_big) {
	EXPECT_FALSE(m1.parse("-1.23x0^0x1^10x2^2"));
}

TEST_F(Fixture_Monom, false_if_to_many_variables) {
	EXPECT_FALSE(m1.parse("-1.23x0^0x1^10x3^2"));
}


TEST_F(Fixture_Monom, compare_operators_is_correct) {
	m1.parse("-1.23x0^0x1^1x2^2");
	m2.parse("x0^0x1^2x2^2");

	EXPECT_TRUE(m1 < m2 && m2 > m1);
}


TEST_F(Fixture_Monom, can_multiplicate) {
	m1.parse("-1.23x0^0x1^1x2^2");

	m1 *= -2;

	std::string s = m1.get_str();

	EXPECT_EQ(m1.get_str(), "2.46x1^1x2^2");
}


TEST_F(Fixture_Monom, can_add) {
	m1.parse("-1.23x0^0x1^1x2^2");
	m2.parse("1x0^0x1^1x2^2");

	m1 += m2;

	EXPECT_EQ(m1.get_str(), "-0.23x1^1x2^2");
}

TEST_F(Fixture_Monom, throw_if_monoms_are_not_similar_for_add) {
	m1.parse("-1.23x0^0x1^1x2^2");
	m2.parse("1x0^0x1^1x2^1");

	ASSERT_ANY_THROW(m1 += m2);
}

TEST_F(Fixture_Monom, can_sub) {
	m1.parse("-1.23x0^0x1^1x2^2");
	m2.parse("1x0^0x1^1x2^2");

	m1 -= m2;

	EXPECT_EQ(m1.get_str(), "-2.23x1^1x2^2");
}

TEST_F(Fixture_Monom, throw_if_monoms_are_not_similar_for_sub) {
	m1.parse("-1.23x0^0x1^1x2^2");
	m2.parse("1x0^0x1^1x2^1");

	ASSERT_ANY_THROW(m1 -= m2);
}