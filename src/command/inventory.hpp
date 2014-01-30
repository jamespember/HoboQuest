#ifndef HOBO_INVENTORY_COMMAND
#define HOBO_INVENTORY_COMMAND

#include "command.hpp"
#include "../actor/player.hpp"

#include <deque>
#include <string>

namespace hoboquest {

  class InventoryCommand : public Command { /*{{{*/
    public:
      InventoryCommand() : Command("inventory", "inv") {}

      CommandOutcome execute(Player &player, std::deque<std::string> &args) {
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

      CommandOutcome execute(Player &player, std::deque<std::string> &args) {
        if (args.empty())
          return player.message("Pick up what?"), ERROR;

        auto &out = player.out();
        auto item = player.location()->get_item(args[0]);

        if (!item) {
          out << "There's nothing called '" << args[0] << "' here!\n";
          return ERROR;
        }

        // Attempt to add item to inventory
        if (!player.pickup(item->id())) {
          out << "You can't pick up " << *item << "." << std::endl; 
          return ERROR;
        }

        return SUCCESS;
      }
  }; /*}}}*/

  class DropCommand : public Command { /*{{{*/
    public:
      DropCommand() : Command("drop", "leave") {}

      CommandOutcome execute(Player &player, std::deque<std::string> &args) {
        if (args.empty())
          return player.message("Drop what?"), ERROR;

        auto &out = player.out();
        auto item = player.get_item(args[0]);

        if (!item) {
          out << "There's nothing called '" << args[0] <<
            "' in your inventory!\n";
          return ERROR;
        }

        // Attempt to drop item in area
        if (!player.drop(item->id())) {
          out << "You can't drop " << *item << " here!" << std::endl; 
          return ERROR;
        }

        return SUCCESS;
      }
  }; /*}}}*/

  class GiveCommand : public Command { /*{{{*/
    public:
      GiveCommand() : Command("give", "g") {}

      CommandOutcome execute(Player &player, std::deque<std::string> &args) {
        if (args.empty())
          return player.message("Give what?"), ERROR;
        if (args.size() < 2)
          return player.message("Give to whom?"), ERROR;


        auto &out = player.out();
        auto actor = player.location()->get_actor(args[0]);

        if (!actor) {
          out << "There's no one around known as '" << args[0] << "'.\n";
          return ERROR;
        }

        auto item = player.get_item(args[1]);

        if (!item) {
          out << "You don't have anything called '" << args[0] << "'.\n";
          return ERROR;
        }

        if (!player.give(actor, item->id())) {
          out << "You can't give " << *item << " to " << *actor << "." << std::endl; 
          return ERROR;
        }

        return SUCCESS;
      }
  }; /*}}}*/

  class StealCommand : public Command { /*{{{*/
    public:
      StealCommand() : Command("steal") {}

      CommandOutcome execute(Player &player, std::deque<std::string> &args) {
        if (args.empty())
          return player.message("Steal what?"), ERROR;
        if (args.size() < 2)
          return player.message("Steal from whom?"), ERROR;

        auto &out = player.out();
        auto actor = player.location()->get_actor(args[0]);

        if (!actor) {
          out << "There's no one around known as '" << args[0] << "'.\n";
          return ERROR;
        }

        auto item = actor->get_item(args[1]);

        if (!item) {
          out << actor->name() << " doesn't have anything called '" << args[0] << "'.\n";
          return ERROR;
        }

        if (!player.steal(actor, item->id())) {
          out << "You can't steal " << *item << " from " << *actor << "." << std::endl; 
          return ERROR;
        }

        return SUCCESS;
      }
  }; /*}}}*/

  class EquipCommand : public Command { /*{{{*/
    public:
      EquipCommand() : Command("equip", "eq") {}

      CommandOutcome execute(Player &player, std::deque<std::string> &args) {
        if (args.empty())
          return player.message("Equip what?"), ERROR;

        auto &out = player.out();
        auto item = player.get_item(args[0]);

        if (!item) {
          out << "There's nothing called '" << args[0] <<
            "' in your inventory!\n";
          return ERROR;
        }

        if (!player.equip(item->id())) {
          out << "You can't equip " << *item << "." << std::endl; 
          return ERROR;
        }

        return SUCCESS;
      }
  }; /*}}}*/

  class UnequipCommand : public Command { /*{{{*/
    public:
      UnequipCommand() : Command("unequip", "un") {}

      CommandOutcome execute(Player &player, std::deque<std::string> &args) {
        if (args.empty())
          return player.message("Unequip what?"), ERROR;

        auto &out = player.out();
        auto item = player.get_equipment(args[0]);

        if (!item) {
          out << "You don't have anything equipped called '" << args[0] << "'\n";
          return ERROR;
        }

        if (!player.unequip(item->id())) {
          out << "You can't unequip " << *item << "." << std::endl; 
          return ERROR;
        }

        return SUCCESS;
      }
  }; /*}}}*/

} /* hoboquest */ 

#endif
