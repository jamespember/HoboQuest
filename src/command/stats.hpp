#ifndef HOBO_STATS_COMMAND
#define HOBO_STATS_COMMAND

#include "command.hpp"
#include "../actor/player.hpp"

#include <memory>
#include <deque>
#include <string>

namespace hoboquest {
  class StatsCommand : public Command {
    public:
      StatsCommand() : Command("stats") {}

      CommandOutcome execute(Player &player, std::deque<std::string> &args) {

        player.describe(player.out());
        return NOOP;
      }
  };
} /* hoboquest */ 

#endif
