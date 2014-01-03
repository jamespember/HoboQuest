#ifndef HOBO_TEST_COMMAND
#define HOBO_TEST_COMMAND

#include "../command/command.hpp"
#include "../player.hpp"

#include <cassert>
#include <list>
#include <string>

using namespace std;
using namespace hoboquest;

namespace {
  struct TestCommand1 : public Command {
    TestCommand1() : Command("test1") {}
    bool execute(Player &player, std::list<std::string> &args) {
      return true;
    }
  };

  struct FailingCommand : public Command {
    FailingCommand() : Command("failing", "fail") {}
    bool execute(Player &player, std::list<std::string> &args) {
      return false;
    }
  };

  struct ArgsCommand : public Command {
    ArgsCommand() : Command("args") {}
    bool execute(Player &player, std::list<std::string> &args) {
      return args.back() == "second";
    }
  };
}

void test_command() {
  Player p(cin, cout);
  list<string> args = {"first", "second"};

  TestCommand1 tc;
  assert(tc.name == "test1");
  assert(tc.has_alias() == false);
  assert(tc.alias.empty());
  assert(tc.execute(p, args) == true);

  FailingCommand fc;
  assert(fc.name == "failing");
  assert(fc.has_alias() == true);
  assert(fc.alias == "fail");
  assert(fc.execute(p, args) == false);

  ArgsCommand ac;
  assert(ac.execute(p, args) == true);
}

#endif
