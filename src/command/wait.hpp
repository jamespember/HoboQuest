#ifndef HOBO_WAIT_COMMAND
#define HOBO_WAIT_COMMAND

#include "command.hpp"

#include <deque>
#include <string>

namespace hoboquest {
  class Player;

  class WaitCommand : public Command {
    public:
      WaitCommand() : Command("wait") {}

      CommandOutcome execute(Player &player, std::deque<std::string> &args) {
        player.message("You stand there, idling...");
        return SUCCESS;
      }
  };
} /* hoboquest */ 

#endif
