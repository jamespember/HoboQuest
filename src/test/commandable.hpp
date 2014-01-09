#ifndef HOBO_TEST_COMMANDABLE
#define HOBO_TEST_COMMANDABLE

#include "../player.hpp"
#include "../command/simple_command.hpp"

#include <cassert>
#include <memory>
#include <list>
#include <string>

#ifndef PTR_SimpleCommand
#define PTR_SimpleCommand make_shared<SimpleCommand>
#endif

using namespace std;
using namespace hoboquest;

void test_commandable() {
  Commandable cmds;
  Player p(cin, cout);
  list<string> args;

  assert(cmds.has_command("test") == false);
  assert(cmds.execute("test", args, p) == CommandOutcome::NOT_FOUND);

  cmds.add_command(PTR_SimpleCommand("test", [](Player &player, list<string> &args) -> bool {
    player.message("test command ran!");
    return true;
  }));

  cmds.add_command(PTR_SimpleCommand("hello", [](Player &player, list<string> &args) -> bool {
    player.message("hello command ran!");
    return true;
  }));

  cmds.add_command(PTR_SimpleCommand("fail", [](Player &player, list<string> &args) -> bool {
    player.message("failing command ran!");
    return false;
  }));

  assert(cmds.has_command("test") == true);
  assert(cmds.has_command("fail") == true);
  assert(cmds.has_command("nope") == false);

  assert(cmds.execute("test", args, p) == CommandOutcome::SUCCESS);
  assert(cmds.execute("hello", args, p) == CommandOutcome::SUCCESS);
  assert(cmds.execute("fail", args, p) == CommandOutcome::ERROR);

  assert(cmds.remove_command("test") == true);
  assert(cmds.has_command("test") == false);

}

#endif
