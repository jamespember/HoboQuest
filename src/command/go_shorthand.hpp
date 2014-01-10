#ifndef HOBO_GO_SHORTHAND_COMMAND
#define HOBO_GO_SHORTHAND_COMMAND

#include "go.hpp"

#include <list>
#include <string>

namespace hoboquest {
  class GoShorthandCommand : public GoCommand {
    public:

      GoShorthandCommand(const std::string &direction, const std::string &alias) :
        GoCommand(direction, alias) {}
      GoShorthandCommand(const std::string &direction) :
        GoCommand(direction) {}

      CommandOutcome execute(Player &player, std::list<std::string> &args) {
        std::list<std::string> go_args { name };
        return GoCommand::execute(player, go_args);
      }

  };
} /* hoboquest */ 

#endif
