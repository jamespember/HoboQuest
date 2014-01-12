#ifndef HOBO_TEST_AREA
#define HOBO_TEST_AREA

#include <memory>
#include <cassert>
#include "../area.hpp"

using namespace std;
using namespace hoboquest;

void test_area() {
	auto house = make_shared<Area>("house", "House");
}

#endif
