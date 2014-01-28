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
#include "../command/inventory.hpp"
#include "../command/interact.hpp"

using namespace std;

namespace hoboquest {
  void initialize_player(shared_ptr<Player> player) {
      //{{{ Commands
      player->commands.add_command(make_shared<HelpCommand>());
      player->commands.add_command(make_shared<DescribeCommand>());
      player->commands.add_command(make_shared<GoCommand>());
      player->commands.add_command(make_shared<GoShorthandCommand>("north", "n"));
      player->commands.add_command(make_shared<GoShorthandCommand>("south", "s"));
      player->commands.add_command(make_shared<GoShorthandCommand>("west", "w"));
      player->commands.add_command(make_shared<GoShorthandCommand>("east", "e"));
      player->commands.add_command(make_shared<GoShorthandCommand>("up", "u"));
      player->commands.add_command(make_shared<GoShorthandCommand>("down", "d"));
      player->commands.add_command(make_shared<InteractCommand>());
      player->commands.add_command(make_shared<InventoryCommand>());
      player->commands.add_command(make_shared<PickupCommand>());
      player->commands.add_command(make_shared<DropCommand>());
      player->commands.add_command(make_shared<ConsumeCommand>());
      player->commands.add_command(make_shared<ExitCommand>());
      //}}}

      //{{{ Player events
      player->observe("picked_up", [player](shared_ptr<Entity> e) {
        player->out() << "Picked up ";
        e->describe(player->out());
        return true;
      });
      player->observe("dropped", [player](shared_ptr<Entity> e) {
        player->out() << "Dropped ";
        e->describe(player->out());
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
