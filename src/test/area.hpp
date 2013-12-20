#ifndef HOBO_TEST_AREA
#define HOBO_TEST_AREA

#include <memory>
#include <cassert>
#include "../area.hpp"

using namespace std;
using namespace hoboquest;

void test_area() {
	auto house = make_shared<Area>("House", "A small wooden house");
	auto garden = make_shared<Area>("Garden", "A beautiful garden");

	// Verify that adding an exit works
	house->add_exit("door", garden);
	assert(house->has_exit("door") == true);
	assert(garden->has_exit("door") == false);
	
	// Verify fetching exit works and that changes are reflected globally
	auto exit = house->get_exit("door"); // exit should now point to garden
	garden->set_name("Big Garden");
	garden->set_description("An amazingly large garden");
	assert(house->name() == "House");
	assert(exit->name() == "Big Garden");
	assert(exit->description() == "An amazingly large garden");

	// Verify that removing an exit works
	house->remove_exit("door");
	assert(house->has_exit("door") == false);
	assert(garden->has_exit("door") == false);
}

#endif
