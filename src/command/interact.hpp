#ifndef HOBO_INTERACT_COMMAND
#define HOBO_INTERACT_COMMAND

#include "command.hpp"
#include "../actor/player.hpp"

#include <deque>
#include <string>

namespace hoboquest {

  class InteractCommand : public Command { /*{{{*/
    public:
      InteractCommand() : Command("interact", "i") {}

      CommandOutcome execute(Player &player, std::deque<std::string> &args) {
        auto location = player.location();

        if (location == nullptr) {
          player.message("You can't interact with anything in the void!");
          return ERROR;
        }

        if (args.empty()) {
          player.message("With what?");
          location->describe_actors(player.out());
          return ERROR;
        }

        auto actor = location->get_actor(args.front());

        if (!actor) {
          player.out() << "Can't interact with '" << args.front() << "'." << std::endl;
          return ERROR;
        }

        if (!player.interact(actor))
          player.message("No response.");

        return SUCCESS;
      }
  }; /*}}}*/

} /* hoboquest */ 

#endif
