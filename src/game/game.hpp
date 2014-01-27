#ifndef HOBO_GAME
#define HOBO_GAME

#include "../engine.hpp"
#include "../item/consumable.hpp"
#include "../item/equippable.hpp"

#include "initialize_player.hpp"

#include "gun_quest.hpp"

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

        // Initialize player
        initialize_player(player);

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

        // {{{ Areas
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
        // }}}

        // {{{ Exits
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
        // }}}

        // Actors
        auto police = make_shared<Actor>("police", "Police officer");
        auto kid = make_shared<Actor>("kid", "Kid");
        auto hobo = make_shared<Actor>("hobo", "Friendly(?) hobo");
        auto manager = make_shared<Actor>("manager", "Manager");
        auto bartender = make_shared<Actor>("bartender", "Bartender");
        auto crazy_joe = make_shared<Actor>("joe", "Crazy Joe");

        // Place actors
        police->move_to(areas.get("main_street"));
        kid->move_to(areas.get("park"));
        manager->move_to(areas.get("floor0"));
        bartender->move_to(areas.get("pub"));
        hobo->move_to(areas.get("shelter"));
        crazy_joe->move_to(areas.get("roof"));

        // Crazy Joe
        areas.get("roof")->observe("on_enter", [this](shared_ptr<Entity> e) {
          if (e == player && this->areas.get("roof")->has_actor("joe")) {
            player->message("Crazy Joe: One step closer and I'll jump! I promise I will!");
            return true;
          }
          return false;
        });
        crazy_joe->observe("interact", [this, crazy_joe](shared_ptr<Entity> e) {
          player->message("Crazy Joe: GERONIMOOOOOO!");
          crazy_joe->go("east");
          crazy_joe->kill();
          crazy_joe->set_description("Corpse of Crazy Joe");
          player->message("Crazy Joe is no more. Happy now?");
          return false;
        });

        // Items
        // {{{ beer @ pub
        auto beer = make_shared<Consumable>("beer", "Beer");
        beer->set_description("A lovely non-alcoholic(?) beverage.");
        beer->set_hp_modifier(-5);
        beer->observe("consumed", [this](shared_ptr<Entity> e) {
        	player->message("You drank the beer and lost 5 hp."); return false;
      	});
        areas.get("pub")->add_item(beer);
        // }}}

        // Actors
        // {{{ cop @ police_station
        auto cop = make_shared<Actor>("cop", "Cop");
        cop->set_description("Random badge-wearer.");
        cop->observe("interact", [&](shared_ptr<Entity> e) {
          if (player->completed_quest("gun_quest")) {
            says(cop, "Thanks for the help before!");
          } else if (!player->has_quest("gun_quest")) {
            says(cop, "Good evening sir. I've lost my sidearm, would you help me find it?");
            make_shared<GunQuest>(*this, areas.get("main_street"), cop)->start();
          } else {
            says(cop, "Found anything?");
          }
          return true;
        });
        areas.get("police_station")->add_actor(cop);
        // }}}

        // Start game
        player->move_to(areas.get("alley"));
      }
  };
}

#endif
