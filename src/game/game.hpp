#ifndef HOBO_GAME
#define HOBO_GAME

#include "../engine.hpp"
#include "../item/consumable.hpp"
#include "../item/equippable.hpp"

#include "initialize_player.hpp"

#include "main_quest.hpp"
#include "gun_quest.hpp"
#include "cat_quest.hpp"

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

    public:
      Game(istream &in, ostream &out) : Engine(in, out) {
        _out << "Welcome to HoboQuest!\n";
        _out << "You are a sad, homeless, piece of junk. To all other \n";
        _out << "characters in the game you are dirt. You need to find\n";
        _out << "a place to live asap so the society will respect you!\n";
        _out << "\n";
        _out << "Important commands:\n";
        _out << "go <direction>       Move between areas\n";
        _out << "pickup <item>        Pick up an item\n";
        _out << "drop <item>          Drop an item in inventory\n";
        _out << "inventory            List items in inventory\n";
        _out << "interact <actor>     Interact with character\n";
        _out << "consume <item>       Eat/drink a consumable item\n";
        _out << "help                 List all commands\n";
        _out << "\n";

        // Initialize player
        initialize_player(player);

        /*
           Roof  ------\
            |          |
          Floor2       |
            |          |
          Floor1 <-----|--- Apartment
            |          |
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
            "Hallway on the first floor of the apartments building.");
        add_area("floor2", "Apartments, 2nd floor",
            "Hallway on the second floor of the apartments building.");
        add_area("roof", "Roof",
            "The rooftop area of a a large apartments building.");
        add_area("apartment", "Apartment",
            "Your very own apartment. It looks rat infested.");
        // }}}

        // {{{ Exits
        connect_areas("alley", "north", "south", "pub");
        connect_areas("alley", "east", "west", "main_street");
        connect_areas("main_street", "east", "west", "shelter");
        connect_areas("main_street", "south", "north", "police_station");
        connect_areas("cell", "east", "west", "police_station");
        connect_areas("market", "south", "north", "main_street");
        connect_areas("market", "west", "east", "floor0");
        connect_areas("market", "east", "west", "park");
        connect_areas("floor0", "up", "down", "floor1");
        connect_areas("floor1", "up", "down", "floor2");
        connect_areas("floor2", "up", "down", "roof");
        areas.get("roof")->add_exit("east", areas.get("market"));
        areas.get("apartment")->add_exit("west", areas.get("floor1"));
        // }}}

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

        cop->observe("interact", [this, cop](shared_ptr<Entity> e) {
          if (player->completed_quest("gun_quest")) {
            talk(cop, "Thanks for the help before!");
          } else if (!player->has_quest("gun_quest")) {
            talk(cop, "Good evening sir. I've lost my sidearm, would you help me find it?");
            make_shared<GunQuest>(*this, areas.get("floor1"), cop)->start();
          } else if (player->has_item("gun")){
            talk(cop, "You found my gun?! May I have it?");
          } else {
            talk(cop, "Found anything?");
          }
          return true;
        });

        areas.get("police_station")->add_actor(cop);
        // }}}
        // {{{ cat_lady @ park
        auto cat_lady = make_shared<Actor>("cat_lady", "Crazy Cat Lady");
        cat_lady->set_description("No one can understand her, not even her cats.");
        cat_lady->move_to(areas.get("park"));

        auto cat_quest = make_shared<CatQuest>(*this, areas, cat_lady);
        cat_lady->observe("interact", [this, cat_lady, cat_quest](shared_ptr<Entity> e) {
          if (player->completed_quest("cat_quest")) {
            talk(cat_lady, "AAAAH GI DI BAAAAAAAAAAH!!!");
          } else if (!player->has_quest("cat_quest")) {
            talk(cat_lady, "AHH GA DI BA DI AAAAAAH!");
            talk(cat_lady, "Find cats ... GAAAAAH ... get money!");
            talk(cat_lady, "AAAHHH GIII DAA BAAAAA");
            cat_quest->start();
            //player->quests.add(cat_quest);
          } else {
            talk(cat_lady, "AAAAH STARTED AAAAAH");
            cat_quest->complete();
          }
          return true;
        });
        // }}}
        // {{{ joe @ roof
        auto crazy_joe = make_shared<Actor>("joe", "Crazy Joe");
        crazy_joe->move_to(areas.get("roof"));

        areas.get("roof")->observe("on_enter", [this](shared_ptr<Entity> e) {
          if (e == player && this->areas.get("roof")->has_actor("joe")) {
            player->message("Crazy Joe: One step closer and I'll jump! I promise I will!");
            return true;
          }
          return false;
        });

        crazy_joe->observe("interact", [this, crazy_joe](shared_ptr<Entity> e) {
          talk(crazy_joe, "GERONIMOOOOOO!");
          crazy_joe->go("east");
          crazy_joe->kill();
          crazy_joe->set_description("Corpse of Crazy Joe");
          player->message("Crazy Joe is no more. Happy now?");
          return false;
        });
        // }}}
        // {{{ kid @ park
        auto kid = make_shared<Actor>("kid", "Kid");
        auto ball = make_shared<Item>("ball", "Football");
        ball->set_value(5);
        kid->add_item(ball);
        kid->observe("interact", [this, kid](shared_ptr<Entity> e) {
            talk(kid, "What's up doc?");
            return true;
        });
        kid->move_to(areas.get("park"));
        // }}}
        // {{{ realtor @ floor0
        auto realtor = make_shared<Actor>("realtor", "Real eastate agent");
        realtor->move_to(areas.get("floor0"));
        // }}}

        auto hobo = make_shared<Actor>("hobo", "Friendly(?) hobo");
        auto bartender = make_shared<Actor>("bartender", "Bartender");

        bartender->move_to(areas.get("pub"));
        hobo->move_to(areas.get("shelter"));

        // Start game
        player->move_to(areas.get("alley"));

        // Start main quest after first move
        player->observe("entered", [this, realtor](shared_ptr<Entity> e) {
          make_shared<MainQuest>(*this, realtor, areas.get("apartment"), areas.get("floor1"))->start();
          return false;
        });
      }
  };
}

#endif

