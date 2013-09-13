#include <cstdlib>
#include <iostream>

#include "test_item.h"
#include "test_input.h"

using std::cout;

int main(int argc, char **argv) {
	cout << "item\n";
	test_item();
	cout << "input\n";
	test_input();

	return 0;
}
