#ifndef HOBO_TEST_GAME
#define HOBO_TEST_GAME

#include <memory>
#include <cassert>
#include "../area.hpp"
#include "../actor.hpp"
#include "../game.hpp"
#include "../item/item.hpp"
#include "../item/equippable.hpp"
#include "../item/consumable.hpp"
#include "../item/container_item.hpp"

using namespace std;
using namespace hoboquest;

/*
=================  TEST GAME MAP =================

                Dark forest
                    |
                    |
    Cliff ------ Forest ------ House ----
                    |            |      |
                    |            |    Cellar
                    |            |
                  Lake ------ Garden

Notes:
test_large() uses the full map.
test_small() only contains House, Cellar, Garden.
==================================================
*/

void test_small() {
  auto house = make_shared<Area>("House", "A small wooden house");
  auto garden = make_shared<Area>("Garden", "A beautiful garden");
  auto cellar = make_shared<Area>("Cellar", "A tiny cellar full of dust");

  auto player = make_shared<Actor>("Player");
  auto troll = make_shared<Actor>("Troll");

  auto bag = make_shared<ContainerItem>("Bag", "A leather bag");
  auto beer = make_shared<Consumable>("Beer", "A lovely beverage");
  auto book = make_shared<Equippable>("Recipe Book", "A book with many brewing recepies");

  garden->add_exit("door", house);
  house->add_exit("front door", garden);
  house->add_exit("stairs", cellar);
  cellar->add_exit("stairs", house);

  garden->add_actor(player);
  cellar->add_actor(troll);

  //TODO add items
}

void test_large() {
  //TODO
}

void test_game() {
  test_small();
  test_large();
}

#endif
