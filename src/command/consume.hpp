#ifndef HOBO_CONSUME_COMMAND
#define HOBO_CONSUME_COMMAND

#include "command.hpp"
#include "../player.hpp"

#include <list>
#include <string>

namespace hoboquest {

  class ConsumeCommand : public Command {
    public:
      ConsumeCommand() : Command("consume", "eat") {}

      CommandOutcome execute(Player &player, std::list<std::string> &args) {
        if (args.empty())
          return player.message("Consume what?"), ERROR;

        auto item = player.get_item(args.front());

        if (!item) {
          player.out() << "You don't carry any item called '" << args.front() << "'\n";
          return ERROR;
        }

        if (player.consume(args.front())) {
          player.out() << "You consume " << *item << std::endl; 
          return SUCCESS;
        }

        player.out() << "'" << args.front() << "' can't be consumed\n";
        return ERROR;
      }
  };
} /* hoboquest */ 

#endif
