#ifndef HOBO_TEST_ACTOR
#define HOBO_TEST_ACTOR

#include <memory>
#include <cassert>
#include "../actor/actor.hpp"

using namespace std;
using namespace hoboquest;

void test_actor() {
  auto id = "thief";
	auto area = make_shared<Area>("house", "House");
	auto actor = make_shared<Actor>(id, "Thief");
	area->add_actor(actor);
	
	// Verify actor name and that area has the actor
	assert(actor->id() == id);
	assert(actor->name() == "Thief");
	assert(area->has_actor(actor->id()) == true);
	assert(area->has_actor("Hufflepuff") == false);
	
	// Verify fetching actor works and that name changes are reflected globally
	auto test = area->get_actor(actor->id());
	actor->set_name("Dirty thief");
	assert(actor->name() == "Dirty thief");
	assert(test->name() == actor->name());
	
	// Verify hp modifiers work properly
	auto police = make_shared<Actor>("police", "Police");
	police->set_hp_max(100);
	police->set_hp(20);
	int modtest = police->modify_hp(-50);
	assert(modtest == -20);
	assert(police->hp() == 0);
	police->set_hp(90);
	modtest = police->modify_hp(50);
	assert(modtest == 10);
	assert(police->hp() == 100);


	// Verify that removing actors from areas work
	area->remove_actor(actor->id());
	assert(area->has_actor(actor->id()) == false);
	
}

#endif
