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
	// cout << area->has_actor(actor->get_name()) << endl;
	auto test = area->get_actor(actor->get_name());

	actor->set_name("Dirty thief");

	// cout << "Area " << area->get_name() << " has actor " << test->get_name();
	// cout << endl;

	area->remove_actor(actor->get_name());
	// cout << area->has_actor(actor->get_name()) << endl;
}

#endif
