#ifndef HOBO_TEST_PLAYER
#define HOBO_TEST_PLAYER

#include "../player.hpp"
#include "../simple_command.hpp"

#include <cassert>
#include <memory>
#include <list>
#include <string>

using namespace std;
using namespace hoboquest;

void test_player() {
  Player p(cin, cout);
  list<string> args;

  assert(p.commands.has_command("test") == false);
  assert(p.execute("test", args) == false);

  #define ADD_CMD p.commands.add_command
  #define PTR_SimpleCommand make_shared<SimpleCommand>

  ADD_CMD(PTR_SimpleCommand("test", [](Player &player, list<string> &args) -> bool {
    player.message("test command ran!");
    return true;
  }));

  ADD_CMD(PTR_SimpleCommand("hello", [](Player &player, list<string> &args) -> bool {
    player.message("hello command ran!");
    return true;
  }));

  ADD_CMD(PTR_SimpleCommand("fail", [](Player &player, list<string> &args) -> bool {
    player.message("failing command ran!");
    return false;
  }));

  assert(p.commands.has_command("test") == true);
  assert(p.commands.has_command("fail") == true);
  assert(p.commands.has_command("nope") == false);

  assert(p.execute("test", args) == true);
  assert(p.execute("hello", args) == true);
  assert(p.execute("fail", args) == false);

  assert(p.commands.remove_command("test") == true);
  assert(p.commands.has_command("test") == false);

}

#endif
