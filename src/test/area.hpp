#ifndef HOBO_TEST_AREA
#define HOBO_TEST_AREA

#include <memory>
#include <cassert>
#include "../area.hpp"

using namespace std;
using namespace hoboquest;

void test_area() {
	auto sp1 = make_shared<Area>("House", "A small wooden house");
	auto sp2 = make_shared<Area>("Garden", "A beautiful garden");

	sp1->add_exit("door", sp2);
	// cout << sp1->has_exit("door") << " " << sp2->has_exit("door") << endl;
	auto exit = sp1->get_exit("door");

	sp2->set_name("Big Garden");
	sp2->set_description("An amazingly large garden");

	// cout << "Area " << sp1->get_name() << " has exit " << exit->get_name();
	// cout << " (" << exit->get_description() << ")" << endl;

	sp1->remove_exit("door");
	// cout << sp1->has_exit("door") << " " << sp2->has_exit("door") << endl;	
}

#endif
