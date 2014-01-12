#ifndef HOBO_TEST_ITEM
#define HOBO_TEST_ITEM

#include <memory>
#include <cassert>
#include <string>
#include <unordered_map>
#include "../item/item.hpp"
#include "../item/equippable.hpp"
#include "../item/consumable.hpp"

using namespace hoboquest;

void test_item() {
  
  auto i1 = make_shared<Item>("1", "No value");
  i1->set_description("No value");
  assert(i1->name() == "No value");
  assert(i1->description() == "No value");
  assert(i1->value() == 1);
  assert(i1->weight() == 1);

  auto i2 = make_shared<Item>("2", "Value 100, Weight 50");
  i2->set_value(100);
  i2->set_weight(50);
  assert(i2->id() == "2");
  assert(i2->value() == 100);
  assert(i2->weight() == 50);

  auto custom = make_shared<Item>("custom", "A weird item");
  assert(custom->value() == 1);
  assert(custom->weight() == 1);
  assert(custom->is_equippable() == false);
  assert(custom->is_consumable() == false);
  
  auto sword = make_shared<Equippable>("sword", "Sword");
  assert(sword->is_equippable() == true);
  assert(sword->is_consumable() == false);
  
  // ContainerItem bag("Bag", "A leather bag");
  // bag.set_capacity(30);
  // bag.set_name("Large bag");
  // assert(bag.capacity() == 30);
  // assert(bag.name() == "Large bag");
  // assert(bag.is_equippable() == false); // TODO: should be equippable too?
  // assert(bag.is_consumable() == false);
  
  auto beer = make_shared<Consumable>("Beer", "A lovely beverage");
  assert(beer->is_equippable() == false);
  assert(beer->is_consumable() == true);
  
  
  // Verify that inheritance works properly
  assert(sword->is_equippable() == true);
  assert(beer->is_consumable() == true);
  assert(sword->is_consumable() == false);
  assert(beer->is_equippable() == false);
  assert(custom->is_consumable() == false);
  assert(custom->is_equippable() == false);
}

#endif
