#ifndef HOBO_INITIALIZE_PLAYER
#define HOBO_INITIALIZE_PLAYER

#include "../entity.hpp"
#include "../player.hpp"

#include "../command/consume.hpp"
#include "../command/describe.hpp"
#include "../command/exit.hpp"
#include "../command/go.hpp"
#include "../command/go_shorthand.hpp"
#include "../command/help.hpp"
#include "../command/interact.hpp"
#include "../command/inventory.hpp"
#include "../command/quest.hpp"

using namespace std;

namespace hoboquest {
  void initialize_player(shared_ptr<Player> player) {
    //{{{ Commands
    #define ADD_CMD(CMD) player->commands.add_command(make_shared<CMD ## Command>());
    ADD_CMD(Help)
    ADD_CMD(Describe)
    ADD_CMD(Go)
    player->commands.add_command(make_shared<GoShorthandCommand>("north", "n"));
    player->commands.add_command(make_shared<GoShorthandCommand>("south", "s"));
    player->commands.add_command(make_shared<GoShorthandCommand>("west", "w"));
    player->commands.add_command(make_shared<GoShorthandCommand>("east", "e"));
    player->commands.add_command(make_shared<GoShorthandCommand>("up", "u"));
    player->commands.add_command(make_shared<GoShorthandCommand>("down", "d"));
    ADD_CMD(Interact)
    ADD_CMD(Inventory)
    ADD_CMD(Pickup)
    ADD_CMD(Drop)
    ADD_CMD(Give)
    ADD_CMD(Steal)
    ADD_CMD(Consume)
    ADD_CMD(Equip)
    ADD_CMD(Unequip)
    ADD_CMD(Quest)
    ADD_CMD(Exit)
    //}}}

    //{{{ Player events
    player->observe("picked_up", [player](shared_ptr<Entity> e) {
      player->out() << "Picked up " << *e << std::endl;
      return true;
    });
    player->observe("dropped", [player](shared_ptr<Entity> e) {
      player->out() << "Dropped " << *e << std::endl;
      return true;
    });
    player->observe("gave", [player](shared_ptr<Entity> e) {
      player->out() << "Gave away " << *e << std::endl;
      return true;
    });
    player->observe("stole", [player](shared_ptr<Entity> e) {
      player->out() << "Stole " << *e << std::endl;
      return true;
    });
    player->observe("equipped", [player](shared_ptr<Entity> e) {
      player->out() << "Equipped " << *e << std::endl;
      return true;
    });
    player->observe("unequipped", [player](shared_ptr<Entity> e) {
      player->out() << "Unequipped " << *e << std::endl;
      return true;
    });
    player->observe("got_money", [player](shared_ptr<Entity> e) {
      player->out() << "You recieved some money, current cash: " << player->money() << std::endl;
      return true;
    });
    player->observe("lost_money", [player](shared_ptr<Entity> e) {
      player->out() << "You lost some money, current cash: " << player->money() << std::endl;
      return true;
    });
    player->observe("entered", [player](shared_ptr<Entity> e) {
      player->out() << "Entering ";
      e->describe(player->out());
      return true;
    });
    player->observe("interact", [player](shared_ptr<Entity> e) {
      if (e == player)
        player->message("You can't interact with yourself, you're not schizophrenic!");
      else
        player->out() << e->name() << " tries to interact with you." << std::endl;
      return true;
    });
    player->observe("quest_started", [player](shared_ptr<Entity> e) {
      auto &out = player->out();
      out << "Quest started: ";
      e->describe(out);
      return true;
    });
    player->observe("quest_progressed", [player](shared_ptr<Entity> e) {
      auto &out = player->out();
      out << "Quest updated: ";
      e->describe(out);
      return true;
    });
    player->observe("quest_completed", [player](shared_ptr<Entity> e) {
      player->out() << "Quest completed: " << e->name() << std::endl;
      return true;
    });
    //}}}
  }
} /* hoboquest */ 

#endif
