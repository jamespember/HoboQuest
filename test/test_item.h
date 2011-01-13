#ifndef HOBO_TEST_ITEM
#define HOBO_TEST_ITEM

#include <cassert>
#include "../hoboquest/item.h"

using namespace hoboquest;

void test_item() {
	Item i1("Item 1, no value");
	assert(i1.name() == "Item 1, no value");
	assert(i1.value() == 0);

	Item i2("2", 100);
	assert(i2.value() == 100);
	assert(i2.name() == "2");
}

#endif
