#ifndef HOBO_INVENTORY_COMMAND
#define HOBO_INVENTORY_COMMAND

#include "command.hpp"
#include "../player.hpp"

#include <list>
#include <string>

namespace hoboquest {

  class InventoryCommand : public Command { /*{{{*/
    public:
      InventoryCommand() : Command("inventory", "inv") {}

      CommandOutcome execute(Player &player, std::list<std::string> &args) {
        auto &out = player.out();
        out << "Player inventory (";
        player.describe_carrying(out);
        out << ")" << std::endl;
        if (!player.has_contents())
          out << "  Nothing in here!" << std::endl;
        else
          player.describe_contents(out);
        return NOOP;
      }
  }; /*}}}*/

  class PickupCommand : public Command { /*{{{*/
    public:
      PickupCommand() : Command("pickup", "take") {}

      CommandOutcome execute(Player &player, std::list<std::string> &args) {
        if (args.empty())
          return player.message("Pick up what?"), ERROR;

        auto item = player.location()->remove_item(args.front());
        auto &out = player.out();

        if (!item) {
          out << "There's nothing called '" << args.front() << "' here!\n";
          return ERROR;
        }

        // Attempt to add item to inventory
        if (!player.add_item(item)) {
          out << "You can't pick up " << *item << "." << std::endl; 
          player.location()->add_item(item);
          return ERROR;
        }

        out << "Picked up " << *item << "." << std::endl; 
        return SUCCESS;
      }
  }; /*}}}*/

  class DropCommand : public Command { /*{{{*/
    public:
      DropCommand() : Command("drop", "leave") {}

      CommandOutcome execute(Player &player, std::list<std::string> &args) {
        if (args.empty())
          return player.message("Drop up what?"), ERROR;

        auto item = player.remove_item(args.front());
        auto &out = player.out();

        if (!item) {
          out << "There's nothing called '" << args.front() <<
            "' in your inventory!\n";
          return ERROR;
        }

        // Attempt to drop item in area
        if (!player.location()->add_item(item)) {
          out << "You can't drop " << *item << " here!" << std::endl; 
          player.add_item(item);
          return ERROR;
        }

        out << "Dropped " << *item << "." << std::endl; 
        return SUCCESS;
      }
  }; /*}}}*/

} /* hoboquest */ 

#endif
