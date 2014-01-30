#ifndef HOBO_TEST_PLAYER
#define HOBO_TEST_PLAYER

#include "../actor/player.hpp"
#include "../command/simple_command.hpp"

#include <cassert>
#include <memory>
#include <deque>
#include <string>

#ifndef PTR_SimpleCommand
#define PTR_SimpleCommand make_shared<SimpleCommand>
#endif

using namespace std;
using namespace hoboquest;

void test_player() {
  Player p(cin, cout);
  deque<string> args;

  assert(p.execute("test", args) == NOT_FOUND);

  p.commands.add_command(PTR_SimpleCommand("test",
        [](Player &player, deque<string> &args) -> bool {
    player.message("test command ran!");
    return true;
  }));

  assert(p.execute("test", args) == SUCCESS);

}

#endif
