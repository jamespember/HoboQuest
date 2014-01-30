#ifndef HOBO_GAME
#define HOBO_GAME

#include "../engine.hpp"
#include "../item/consumable.hpp"
#include "../item/equippable.hpp"

#include "initialize_player.hpp"

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
        _out << "Welcome to HoboQuest!\n";
        _out << "You are a sad, homeless, piece of junk. To all other \n";
        _out << "characters in the game you're dirt. You need to get a\n";
        _out << "place to live asap so the society will respect you!\n";
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
            "Hallway on the first floor of the aparments building.");
        add_area("floor2", "Apartments, 2nd floor",
            "Hallway on the second floor of the aparments building.");
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
            says(cop, "Thanks for the help before!");
          } else if (!player->has_quest("gun_quest")) {
            says(cop, "Good evening sir. I've lost my sidearm, would you help me find it?");
            make_shared<GunQuest>(*this, areas.get("floor1"), cop)->start();
          } else {
            says(cop, "Found anything?");
          }
          return true;
        });

        areas.get("police_station")->add_actor(cop);
        // }}}
        
        
        // {{{ cat_lady @ park
        auto cat_lady = make_shared<Actor>("cat_lady", "Crazy Cat Lady");
        cat_lady->move_to(areas.get("park"));
        auto cat_quest = make_shared<CatQuest>(*this, areas, cat_lady);
        cat_lady->observe("interact", [&, cat_lady](shared_ptr<Entity> e) {
         	if (player->completed_quest("cat_quest")) {
           	says(cat_lady, "AAAAH GI DI BAAAAAAAAAAH!!!");
          } else if (!player->has_quest("cat_quest")) {
        		says(cat_lady, "AHH GA DI BA DI AAAAAAH!");
		    		says(cat_lady, "Find cats ... GAAAAAH ... get money!");
		    		says(cat_lady, "AAAHHH GIII DAA BAAAAA");
            cat_quest->start();
            //player->quests.add(cat_quest);
          } else {
            says(cat_lady, "AAAAH STARTED AAAAAH");
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
          says(crazy_joe, "GERONIMOOOOOO!");
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
            says(kid, "What's up doc?");
            return true;
        });
        kid->move_to(areas.get("park"));
        // }}}
        // {{{ realtor @ floor0
        auto realtor = make_shared<Actor>("realtor", "Real eastate agent");
        realtor->move_to(areas.get("floor0"));
        realtor->observe("interact", [this, realtor](shared_ptr<Entity> e) {
          auto floor1 = areas.get("floor1");
          auto apartment = areas.get("apartment");
          if (player->money() >= 1000 && !floor1->has_exit("east")) {
            says(realtor, "Hey pal, I'm sure you want to buy this fine apartment!");
            says(realtor, "It's only $1000, rats are guaranteed.");
            says(realtor, "Nice, it's located on the first floor.");
            says(realtor, "Thanks for the deal sucker, see you later!");
            realtor->give_money(player->take_money(1000));
            floor1->add_exit("east", apartment);
            apartment->observe("on_enter", [this](shared_ptr<Entity> e) {
              if (e != player) return true;
              player->message("You've completed the game by acquiring a living space!");
              player->message("Welcome to your new apartment!");
              player->message("A hero is you!");
              return false;
            });
          } else if (floor1->has_exit("east")) {
            says(realtor, "I hope you like your new apartment!");
          } else {
            says(realtor, "Come back when you got some money, punk!");
          }
          return true;
        });
        // }}}

        auto hobo = make_shared<Actor>("hobo", "Friendly(?) hobo");
        auto bartender = make_shared<Actor>("bartender", "Bartender");

        bartender->move_to(areas.get("pub"));
        hobo->move_to(areas.get("shelter"));

        // Start game
        player->give_money(1000);
        player->move_to(areas.get("alley"));
      }
  };
}

#endif

