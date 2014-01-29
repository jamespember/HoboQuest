#ifndef HOBO_EXIT_COMMAND
#define HOBO_EXIT_COMMAND

#include "command.hpp"

#include <deque>
#include <string>

namespace hoboquest {
  class Player;

  class ExitCommand : public Command {
    public:
      ExitCommand() : Command("exit", "quit") {}

      CommandOutcome execute(Player &player, std::deque<std::string> &args) {
        return EXIT;
      }
  };
} /* hoboquest */ 

#endif
