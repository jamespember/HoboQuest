#ifndef HOBO_TEST_ITEM
#define HOBO_TEST_ITEM

#include <cassert>
#include "../item/item.hpp"

using namespace hoboquest;

void test_item() {
	Item i1("Item 1, no value");
	assert(i1.name() == "Item 1, no value");
	assert(i1.value() == 1);
	assert(i1.weight() == 1);
	assert(i1.type() == Item::Type::Equippable);

	Item i2("2", 100);
	assert(i2.value() == 100);
	assert(i2.name() == "2");
	assert(i2.type() == Item::Type::Equippable);

  Item custom("Custom");
  assert(custom.value() == 1);
  assert(custom.weight() == 1);
}

#endif
