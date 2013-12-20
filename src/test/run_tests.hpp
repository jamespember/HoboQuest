#include <iostream>

#define TEST(NAME) \
  std::cout << "TESTING " << #NAME << std::endl; \
  test_ ## NAME ();
 
#include "item.hpp"
#include "container.hpp"
#include "area.hpp"
#include "actor.hpp"
#include "input.hpp"

using std::cout;

int run_tests() {
  cout << "Running test suite...\n";

  TEST(item)
  TEST(container)
  TEST(area)
  TEST(actor)
  TEST(input)

  cout << "All tests passed!\n";

	return 0;
}
