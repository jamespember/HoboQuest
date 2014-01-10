#ifndef HOBO_HELP_COMMAND
#define HOBO_HELP_COMMAND

#include "command.hpp"
#include "../player.hpp"

#include <list>
#include <string>

namespace hoboquest {
  class Player;

  class HelpCommand : public Command {
    public:
      HelpCommand() : Command("help", "h") {}

      bool execute(Player &player, std::list<std::string> &args) {
        player.message("Available commands:");
        player.out() << player.commands;
        return false;
      }
  };
} /* hoboquest */ 

#endif
