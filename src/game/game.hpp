#ifndef HOBO_GAME
#define HOBO_GAME

#include "../engine.hpp"
#include "../item/consumable.hpp"
#include "../item/equippable.hpp"

#include "../command/consume.hpp"
#include "../command/describe.hpp"
#include "../command/exit.hpp"
#include "../command/go.hpp"
#include "../command/go_shorthand.hpp"
#include "../command/help.hpp"
#include "../command/inventory.hpp"
#include "../command/interact.hpp"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace hoboquest {
  class Game : public Engine {
    protected:

      void add_area(const string &id, const string &name,
          const string &description) {
        auto area = make_shared<Area>(id, name);
        area->set_description(description);
        areas.add(area);
      }

      void connect_areas(const string &area_a, const string &dir_a,
          const string &dir_b, const string &area_b) {
        if (!areas.has(area_a) || !areas.has(area_b)) {
          _out << "Can't connect '" << area_a << "' with '" << area_b << "'\n";
          return;
        }

        auto a = areas.get(area_a), b = areas.get(area_b);
        a->add_exit(dir_a, b);
        b->add_exit(dir_b, a);
      }

      void says(shared_ptr<Entity> who, const string &what) {
        player->out() << who->name() << " says: " << what << std::endl;
      }

    public:
      Game(istream &in, ostream &out) : Engine(in, out) {
        _out << "Starting HoboQuest...\n";

        add_area("alley", "Dark alley",
            "Starting area.");
        add_area("main_street", "Main street",
            "The main street of the town, plenty of places to go from here.");
        add_area("market", "Market",
            "The town market. There are not many people around right now.");
        add_area("pub", "Pub",
            "A pub filled with people, more or less drunk.");
        add_area("shelter", "Homeless shelter",
            "A state-owned homeless shelter for people lacking a home.");
        add_area("park", "Park",
            "A park with plenty of park benches.");
        add_area("police_station", "Police station",
            "The town police station.");
        add_area("cell", "Jail cell",
            "A jail cell inside the police station.");
        add_area("floor0", "Apartments, bottom floor",
            "Bottom floor of a large apartments building.");
        add_area("floor1", "Apartments, 1st floor",
            "Hallway on the first floor of the aparments building.");
        add_area("floor2", "Apartments, 2nd floor",
            "Hallway on the second floor of the aparments building.");
        add_area("roof", "Roof",
            "The rooftop area of a a large apartments building.");

        /*
           Roof  ------\
            |          |
          Floor2       |
            |          |
          Floor1       v
            |
          Floor0 --- Market ------- Park
                       |
           Pub         |
            |          |
          Alley -- Main street --- Shelter
                       |
           Cell - Police station
        */

        // Exits
        connect_areas("alley", "north", "south", "pub");
        connect_areas("alley", "east", "west", "main_street");
        connect_areas("main_street", "east", "west", "shelter");
        connect_areas("main_street", "south", "north", "police_station");
        connect_areas("cell", "east", "west", "police_station");
        connect_areas("market", "south", "north", "main_street");
        connect_areas("market", "west", "east", "floor0");
        connect_areas("floor0", "up", "down", "floor1");
        connect_areas("floor1", "up", "down", "floor2");
        connect_areas("floor2", "up", "down", "roof");
        areas.get("roof")->add_exit("east", areas.get("market"));

        // Items
        auto beer = make_shared<Consumable>("beer", "Beer");
        beer->set_description("A lovely non-alcoholic(?) beverage.");
        beer->set_hp_modifier(-5);
        areas.get("pub")->add_item(beer);

        // Player events
        player->observe("enter_area", [this](shared_ptr<Entity> e) {
          player->out() << "Entering ";
          e->describe(player->out());
          return true;
        });
        player->observe("interact", [this](shared_ptr<Entity> e) {
          if (e == player)
            player->message("You can't interact with yourself, you're not schizophrenic!");
          else
            player->out() << e->name() << " tries to interact with you." << std::endl;
          return true;
        });

        // Commands
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

        // Actors
        auto cop = make_shared<Actor>("cop", "Cop");
        cop->set_description("Random badge-wearer.");
        cop->observe("interact", [&](shared_ptr<Entity> e) {
          says(cop, "Good evening sir.");
          return true;
        });
        areas.get("police_station")->add_actor(cop);

        // Initialize player
        player->move_to(areas.get("alley"));
      }
  };
}

#endif
