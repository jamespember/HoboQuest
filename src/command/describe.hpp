#ifndef HOBO_DESCRIBE_COMMAND
#define HOBO_DESCRIBE_COMMAND

#include "command.hpp"
#include "../player.hpp"

#include <memory>
#include <list>
#include <string>

namespace hoboquest {
  class DescribeCommand : public Command {
    public:
      DescribeCommand() : Command("describe", "desc") {}

      CommandOutcome execute(Player &player, std::list<std::string> &args) {
        std::shared_ptr<Entity> entity;

        if (args.empty())
          entity = player.location();
        if (!entity)
          entity = player.location()->get_item(args.front());
        if (!entity)
          entity = player.get_item(args.front());
        if (!entity)
          entity = player.location()->get_actor(args.front());
        if (!entity)
          entity = player.quests.get(args.front());

        if (!entity) {
          player.out() << "Can't find anything called '" << args.front() <<
            "' in the vicinity." << std::endl; 
          return ERROR;
        }

        entity->describe(player.out());
        return NOOP;
      }
  };
} /* hoboquest */ 

#endif
