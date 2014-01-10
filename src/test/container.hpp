#ifndef HOBO_TEST_CONTAINER
#define HOBO_TEST_CONTAINER

#include <memory>
#include <cassert>
#include "../container_entity.hpp"
#include "../item/item.hpp"

using namespace std;
using namespace hoboquest;

void test_container() {
  ContainerEntity c(Entity::ITEM, "container", "Container");
  assert(c.capacity() == 100);
  assert(c.carrying() == 0);
  assert(c.money() == 0);
  assert(c.over_encumbered() == false);

  c.give_money(100);
  assert(c.money() == 100);
  assert(c.take_money(50) == 50);
  assert(c.money() == 50);
  assert(c.take_money(100) == 50);
  assert(c.money() == 0);
  c.give_money(10);
  assert(c.money() == 10);

  c.set_capacity(10);
  assert(c.capacity() == 10);
  assert(c.over_encumbered() == false);

  assert(c.has_item("unknown_item") == false);
  assert(c.get_item("unknown_item") == nullptr);
  assert(c.remove_item("unknown_item") == nullptr);

  auto i1 = make_shared<Item>("1", "One");
  auto i2 = make_shared<Item>("2", "Two");
  auto i4 = make_shared<Item>("4", "Three");
  auto i5 = make_shared<Item>("5", "Four");
  i2->set_weight(2);
  i4->set_weight(4);
  i5->set_weight(5);

  assert(c.add_item(i1) == true);
  assert(c.has_item("1") == true);
  assert(c.carrying() == 1);
  assert(c.over_encumbered() == false);
  auto sp_i1 = c.get_item("1");
  assert(sp_i1 != nullptr);
  assert(sp_i1.get() == i1.get());

  assert(c.add_item(i1) == false);

  assert(c.add_item(i5) == true);
  assert(c.carrying() == 6);
  assert(c.over_encumbered() == false);
  assert(c.add_item(i2) == true);
  assert(c.add_item(i4) == true);
  assert(c.carrying() == 12);
  assert(c.over_encumbered() == true);

  assert(c.remove_item("5").get() == i5.get());
  assert(c.get_item("5") == nullptr);
  assert(c.carrying() == 7);
  assert(c.over_encumbered() == false);
}

#endif
