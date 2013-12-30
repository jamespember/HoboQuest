#ifndef HOBO_TEST_PLAYER
#define HOBO_TEST_PLAYER

#include "../player.hpp"
#include "../simple_command.hpp"

#include <cassert>
#include <memory>
#include <list>
#include <string>

#ifndef PTR_SimpleCommand
#define PTR_SimpleCommand make_shared<SimpleCommand>
#endif

using namespace std;
using namespace hoboquest;

void test_player() {
  Player p(cin, cout);
  list<string> args;

  assert(p.execute("test", args) == false);

  p.commands.add_command(PTR_SimpleCommand("test",
        [](Player &player, list<string> &args) -> bool {
    player.message("test command ran!");
    return true;
  }));

  assert(p.execute("test", args) == true);

}

#endif
