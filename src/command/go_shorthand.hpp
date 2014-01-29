#ifndef HOBO_GO_SHORTHAND_COMMAND
#define HOBO_GO_SHORTHAND_COMMAND

#include "go.hpp"

#include <deque>
#include <string>

namespace hoboquest {
  class GoShorthandCommand : public GoCommand {
    public:

      GoShorthandCommand(const std::string &direction, const std::string &alias) :
        GoCommand(direction, alias) {}
      GoShorthandCommand(const std::string &direction) :
        GoCommand(direction) {}

      CommandOutcome execute(Player &player, std::deque<std::string> &args) {
        std::deque<std::string> go_args { name };
        return GoCommand::execute(player, go_args);
      }

  };
} /* hoboquest */ 

#endif
