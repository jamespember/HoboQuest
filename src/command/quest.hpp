#ifndef HOBO_QUEST_COMMAND
#define HOBO_QUEST_COMMAND

#include "command.hpp"
#include "../actor/player.hpp"

#include <memory>
#include <deque>
#include <string>

namespace hoboquest {
  class QuestCommand : public Command {
    public:
      QuestCommand() : Command("quests") {}

      CommandOutcome execute(Player &player, std::deque<std::string> &args) {
        auto &out = player.out();

        if (player.quests.get_map().empty()) {
          out << "  No quests yet" << std::endl;
          return NOOP;
        }

        out << "Quests:" << std::endl;
        for (const auto &kv : player.quests.get_map()) {
          out << "* " << *(kv.second) << std::endl;
          kv.second->describe_stages(out);
        }

        return NOOP;
      }
  };
} /* hoboquest */ 

#endif
