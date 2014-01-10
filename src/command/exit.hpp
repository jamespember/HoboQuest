#ifndef HOBO_EXIT_COMMAND
#define HOBO_EXIT_COMMAND

#include "command.hpp"
#include "../player.hpp"

#include <list>
#include <string>

namespace hoboquest {
  class Player;

  class ExitCommand : public Command {
    public:
      ExitCommand() : Command("exit", "quit") {}

      CommandOutcome execute(Player &player, std::list<std::string> &args) {
        return EXIT;
      }
  };
} /* hoboquest */ 

#endif
