#ifndef HOBO_TEST_ACTOR
#define HOBO_TEST_ACTOR

#include <memory>
#include <cassert>
#include "../actor.hpp"

using namespace std;
using namespace hoboquest;

void test_actor() {
	auto area = make_shared<Area>("House", "A small wooden house");
	auto actor = make_shared<Actor>("Thief");
	area->add_actor(actor);
	
	// Verify actor name and that area has the actor
	assert(actor->get_name() == "Thief");
	assert(area->has_actor(actor->get_name()) == true);
	assert(area->has_actor("Hufflepuff") == false);
	
	// Verify fetching actor works and that name changes are reflected globally
	auto test = area->get_actor(actor->get_name());
	actor->set_name("Dirty thief");
	assert(actor->get_name() == "Dirty thief");
	assert(test->get_name() == actor->get_name());

	// Verify that removing actors from areas work
	area->remove_actor(actor->get_name());
	assert(area->has_actor(actor->get_name()) == false);
	
}

#endif
