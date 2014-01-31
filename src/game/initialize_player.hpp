#ifndef HOBO_INITIALIZE_PLAYER
#define HOBO_INITIALIZE_PLAYER

#include "../entity.hpp"
#include "../actor/player.hpp"

#include "../command/consume.hpp"
#include "../command/describe.hpp"
#include "../command/exit.hpp"
#include "../command/go.hpp"
#include "../command/go_shorthand.hpp"
#include "../command/help.hpp"
#include "../command/interact.hpp"
#include "../command/inventory.hpp"
#include "../command/stats.hpp"
#include "../command/quest.hpp"
#include "../command/wait.hpp"

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
    ADD_CMD(Stats)
    ADD_CMD(Inventory)
    ADD_CMD(Pickup)
    ADD_CMD(Drop)
    ADD_CMD(Give)
    ADD_CMD(Pickpocket)
    ADD_CMD(Consume)
    ADD_CMD(Equip)
    ADD_CMD(Unequip)
    ADD_CMD(Quest)
    ADD_CMD(Wait)
    ADD_CMD(Exit)
    //}}}

    //{{{ Player events
    player->observe("picked_up", [player](shared_ptr<Entity> e) {
      player->out() << "Picked up " << *e << "." << endl;
      return true;
    });
    player->observe("dropped", [player](shared_ptr<Entity> e) {
      player->out() << "Dropped " << *e << "." << endl;
      return true;
    });
    player->observe("gave", [player](shared_ptr<Entity> e) {
      player->out() << "Gave away " << *e << "." << endl;
      return true;
    });
    player->observe("stole", [player](shared_ptr<Entity> e) {
      player->out() << "Stole " << *e << "." << endl;
      return true;
    });
    player->observe("equipped", [player](shared_ptr<Entity> e) {
      player->out() << "Equipped " << *e << "." << endl;
      return true;
    });
    player->observe("unequipped", [player](shared_ptr<Entity> e) {
      player->out() << "Unequipped " << *e << "." << endl;
      return true;
    });
    player->observe("entered", [player](shared_ptr<Entity> e) {
      player->out() << "Entering " << *e << "." << endl;
      return true;
    });
    player->observe("location_added_actor", [player](shared_ptr<Entity> e) {
      player->out() << *e << " entered the area." << endl;
      return true;
    });
    player->observe("location_removed_actor", [player](shared_ptr<Entity> e) {
      auto actor = static_pointer_cast<Actor>(e);
      player->out() << *e << " left the area, heading towards " << *(actor->location()) << "." << endl;
      return true;
    });
    player->observe("interacted", [player](shared_ptr<Entity> e) {
      if (e == player)
        player->message("You can't interact with yourself, you're not schizophrenic!");
      else
        player->out() << e->name() << " wants to interact with you." << endl;
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
      player->out() << "Quest completed: " << e->name() << endl;
      return true;
    });
    //}}}
  }
} /* hoboquest */ 

#endif
