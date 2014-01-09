#ifndef HOBO_TEST_ITEM
#define HOBO_TEST_ITEM

#include <cassert>
#include <string>
#include <unordered_map>
#include "../item/item.hpp"
#include "../item/equippable.hpp"
#include "../item/consumable.hpp"

using namespace hoboquest;

void test_item() {

  std::unordered_map<std::string, Item*> items;
  
  Item i1("1", "No value");
  i1.set_description("No value");
  items[i1.name()] = &i1;
  assert(i1.name() == "No value");
  assert(i1.description() == "No value");
  assert(i1.value() == 1);
  assert(i1.weight() == 1);

  Item i2("2", "Value 100, Weight 50");
  items[i2.name()] = &i2;
  i2.set_value(100);
  i2.set_weight(50);
  assert(i2.id() == "2");
  assert(i2.value() == 100);
  assert(i2.weight() == 50);

  Item custom("custom", "A weird item");
  items[custom.name()] = &custom;
  assert(custom.value() == 1);
  assert(custom.weight() == 1);
  assert(custom.is_equippable() == false);
  assert(custom.is_container() == false);
  assert(custom.is_consumable() == false);
  
  Equippable sword("sword", "Sword");
  items[sword.name()] = &sword;
  assert(sword.is_equippable() == true);
  assert(sword.is_container() == false);
  assert(sword.is_consumable() == false);
  
  // ContainerItem bag("Bag", "A leather bag");
  // bag.set_capacity(30);
  // bag.set_name("Large bag");
  // items[bag.name()] = &bag;
  // assert(bag.capacity() == 30);
  // assert(bag.name() == "Large bag");
  // assert(bag.is_equippable() == false); // TODO: should be equippable too?
  // assert(bag.is_container() == true);
  // assert(bag.is_consumable() == false);
  
  Consumable beer("Beer", "A lovely beverage");
  items[beer.name()] = &beer;
  assert(beer.is_equippable() == false);
  assert(beer.is_container() == false);
  assert(beer.is_consumable() == true);
  
  
  // Verify that inheritance works properly
  // assert(items[bag.name()]->is_container() == true);
  assert(items[sword.name()]->is_equippable() == true);
  assert(items[beer.name()]->is_consumable() == true);
  // assert(items[bag.name()]->is_consumable() == false);
  assert(items[sword.name()]->is_container() == false);
  assert(items[sword.name()]->is_consumable() == false);
  assert(items[beer.name()]->is_equippable() == false);
  assert(items[beer.name()]->is_container() == false);
  assert(items[custom.name()]->is_container() == false);
  assert(items[custom.name()]->is_consumable() == false);
  assert(items[custom.name()]->is_equippable() == false);
}

#endif
