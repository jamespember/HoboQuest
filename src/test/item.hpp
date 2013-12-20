#ifndef HOBO_TEST_ITEM
#define HOBO_TEST_ITEM

#include <cassert>
#include "../item/item.hpp"
#include "../item/equippable.hpp"
#include "../item/consumable.hpp"

using namespace hoboquest;

void test_item() {
	Item i1("Item 1, no value");
	assert(i1.name() == "Item 1, no value");
	assert(i1.value() == 1);
	assert(i1.weight() == 1);

	Item i2("2", 100);
	assert(i2.value() == 100);
	assert(i2.name() == "2");

  Item custom("Custom");
  assert(custom.value() == 1);
  assert(custom.weight() == 1);
  assert(custom.is_equippable() == false);
  assert(custom.is_container() == false);
  assert(custom.is_consumable() == false);
  
  Equippable sword("Sword");
  assert(sword.is_equippable() == true);
  assert(sword.is_container() == false);
  assert(sword.is_consumable() == false);
  
  /*
  Container bag("Bag");
  assert(bag.is_equippable() == false); // TODO: should be equippable too?
  assert(bag.is_container() == true);
  assert(bag.is_consumable() == false);
	*/
	
  Consumable beer("Beer");
  assert(beer.is_equippable() == false);
  assert(beer.is_container() == false);
  assert(beer.is_consumable() == true);
}

#endif
