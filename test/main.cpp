#include <cstdlib>
#include <iostream>

#include "item.hpp"
#include "input.hpp"

using std::cout;

int main(int argc, char **argv) {
	cout << "item\n";
	test_item();
	cout << "input\n";
	test_input();

  cout << "ALL TESTS PASSED\n";

	return 0;
}
