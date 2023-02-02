#include <gtest.h>

#include "Polynom.h"

void print_v(std::vector<size_t> v) {
	for (auto i : v) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
}

int main(int argc, char **argv)
{
	std::string s = "x0^2";

	Monom<3, 10> m(s);

	std::cout << (m.get_coef()) << std::endl;
	print_v(m.get_degree());

  //::testing::InitGoogleTest(&argc, argv);
  //return RUN_ALL_TESTS();
}
