#ifndef HOBO_TEST_MOVEMENT
#define HOBO_TEST_MOVEMENT

#include "../player.hpp"
#include "../area.hpp"
#include "../command/go.hpp"
#include "../command/go_shorthand.hpp"

#include <cassert>
#include <memory>
#include <list>
#include <string>

using namespace std;
using namespace hoboquest;

void test_movement() {
  auto player = make_shared<Player>(cin, cout);
  auto args = list<string>();

  auto house = make_shared<Area>("House", "");
  auto garden = make_shared<Area>("Garden", "");
  auto cellar = make_shared<Area>("Cellar", "");

  house->add_exit("south", garden);
  house->add_exit("east", cellar);
  garden->add_exit("north", house);
  cellar->add_exit("west", house);

  // auto npc = make_shared<Actor>("npc");

  player->move_to(house);
  player->commands.add_command(make_shared<GoCommand>());
  args.push_back("west");
  assert(player->execute("go", args) == false);
  assert(player->location() == house);
  args.clear();
  args.push_back("east");
  assert(player->execute("go", args) == true);
  assert(player->location() == cellar);
  assert(player->execute("go", args) == false);
  assert(player->location() == cellar);

  player->commands.add_command(make_shared<GoShorthandCommand>("west", "w"));
  args.clear();
  assert(player->execute("west", args) == true);
  assert(player->location() == house);

  assert(player->execute("east", args) == false);
  assert(player->location() == house);
}

#endif
