#include <cstdlib>
#include <iostream>

#define TEST(NAME) \
  std::cout << "TESTING " << #NAME << std::endl; \
  test_ ## NAME ();
  

#include "item.hpp"
#include "container.hpp"
#include "input.hpp"

using std::cout;

int main(int argc, char **argv) {
  TEST(item)
  TEST(container)
  TEST(input)

  cout << "ALL TESTS PASSED\n";

	return 0;
}
