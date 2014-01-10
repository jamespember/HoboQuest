#ifndef HOBO_GO_COMMAND
#define HOBO_GO_COMMAND

#include "command.hpp"

#include <list>
#include <string>

namespace hoboquest {
  class GoCommand : public Command {
    public:
      GoCommand(const std::string &direction, const std::string &alias);
      GoCommand(const std::string &direction);
      GoCommand();

      CommandOutcome execute(Player &player, std::list<std::string> &args);

  };
} /* hoboquest */ 

#endif
