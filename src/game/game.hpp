#ifndef HOBO_GAME
#define HOBO_GAME

#include "../engine.hpp"
#include "../item/consumable.hpp"
#include "../item/equippable.hpp"
#include "../actor/ranger.hpp"
#include "../shop.hpp"

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

      void add_area(std::shared_ptr<Area> area) {
        areas.add(area);
      }

      void add_area(const string &id, const string &name,
          const string &description) {
        auto area = make_shared<Area>(id, name);
        area->set_description(description);
        areas.add(area);
      }

    public:
      Game(istream &in, ostream &out) : Engine(in, out) {
        // {{{ Output welcome text
        _out << "Welcome to HoboQuest!\n";
        _out << "You are a sad, homeless, piece of junk. To all other \n";
        _out << "characters in the game you are dirt. You need to find\n";
        _out << "a place to live asap so society will respect you!\n";
        _out << "\n";
        _out << "Important commands:\n";
        _out << "help                 List all commands\n";
        _out << "go <direction>       Move between areas (shorthand aliases available)\n";
        _out << "pickup <item>        Pick up an item\n";
        _out << "drop <item>          Drop an item in inventory\n";
        _out << "inventory            List items in inventory\n";
        _out << "interact <actor>     Interact with character\n";
        _out << "consume <item>       Eat/drink a consumable item\n";
        _out << "\n";
        // }}}

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
        auto pub = make_shared<Shop>("pub", "Pub", *this);
        pub->set_description("A pub filled with people, more or less drunk.");
        add_area(pub);

        areas.get("pub")->observe("on_enter", [this](shared_ptr<Entity> e) {
          if (e == player) {
            player->message("Tip: in here you can use the command \"buy <item>\" to buy an item.");
          }
          return true;
        });
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
        beer->set_value(10);
        beer->observe("consumed", [this, beer, pub](shared_ptr<Entity> e) {
          player->message("You drank the beer and lost 5 hp.");
          pub->stock_add(beer); return true;
        });
        pub->stock_add(beer);


        auto juice = make_shared<Consumable>("juice", "Juice");
        juice->set_description("A fruitful beverage.");
        juice->set_hp_modifier(10);
        juice->set_value(50);
        juice->observe("consumed", [this, juice, pub](shared_ptr<Entity> e) {
          player->message("You drank the juice and got 10 hp!"); 
          pub->stock_add(juice); return true;
        });
        pub->stock_add(juice);


        // }}}

        // Actors
        // {{{ cop @ police_station
        auto cop = make_shared<Actor>("cop", "Cop");
        cop->set_description("Random badge-wearer.");
        add_actor(cop, "police_station");

        cop->observe("interacted", [this, cop](shared_ptr<Entity> e) {
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
        // }}}
        // {{{ cat_lady @ park
        auto cat_lady = make_shared<Actor>("cat_lady", "Crazy Cat Lady");
        cat_lady->set_description("No one can understand her, not even her cats.");
        add_actor(cat_lady, "park");

        auto cat_quest = make_shared<CatQuest>(*this, areas, cat_lady);
        
        cat_lady->observe("interacted", [this, cat_lady, cat_quest](shared_ptr<Entity> e) {
          if (player->completed_quest("cat_quest")) {
            talk(cat_lady, "AAAAH GI DI BAAAAAAAAAAH!!!");
          } else if (!player->has_quest("cat_quest")) {
            talk(cat_lady, "AHH GA DI BA DI AAAAAAH!");
            talk(cat_lady, "Find cats ... GAAAAAH ... for DAAAAAAAH meAAAAH!");
            talk(cat_lady, "AAAHHH GIII DAA BAAAAA");
            cat_quest->start();
          } else {
            if (cat_quest->has_all_cats()) {
              cat_quest->complete();
              talk(cat_lady, "GAAAAAAAAAAAAH CAAAAAAAAATS!!!");  
            } else {
              talk(cat_lady, "BAAAAAH MORE CATS GLAAAAAAAAHH!");  
            }
          }
          return true;
        });
        // }}}
        // {{{ joe @ roof
        auto joe = make_shared<Actor>("joe", "Crazy Joe");
        add_actor(joe, "roof");

        areas.get("roof")->observe("on_enter", [this](shared_ptr<Entity> e) {
          if (e == player && this->areas.get("roof")->has_actor("joe")) {
            player->message("Crazy Joe: One step closer and I'll jump! I promise I will!");
            return true;
          }
          return false;
        });

        joe->observe("interacted", [this, joe](shared_ptr<Entity> e) {
          talk(joe, "GERONIMOOOOOO!");
          joe->go("east");
          joe->kill();
          joe->set_description("Corpse of Crazy Joe");
          player->message("Crazy Joe is no more. Happy now?");
          return false;
        });
        // }}}
        // {{{ kid @ park
        auto kid = make_shared<Actor>("kid", "Kid");
        auto ball = make_shared<Item>("ball", "Football");
        ball->set_value(5);
        kid->add_item(ball);
        kid->add_money(10);
        kid->observe("interacted", [this, kid](shared_ptr<Entity> e) {
          if (kid->has_item("ball"))
            talk(kid, "What's up doc?");
          else if (player->has_item("ball"))
            talk(kid, "You've got my ball? Please give it back!");
          else
            talk(kid, "Someone took my ball! Could you help me find it?");
          return true;
        });
        kid->observe("added_item", [this, kid, ball](shared_ptr<Entity> e) {
          if (e != ball) {
            talk(kid, "What's this?");
            return true;
          }
          talk(kid, "Hey, that's my ball, thanks!");
          if (kid->money() < 1) {
            talk(kid, "I'd give you a reward but someone stole my lunch money.");
          } else {
            talk(kid, "Here, have my lunch money as a reward.");
            player->add_money(kid->remove_money());
          }
          return false;
        });
        kid->observe("tick", [this, kid](shared_ptr<Entity> e) {
          if (kid->has_item("ball"))
            return true;
          talk(kid, "Hey, who took my ball?!");
          return false;
        });
        add_actor(kid, "park");
        // }}}
        // {{{ realtor @ floor0
        auto realtor = make_shared<Actor>("realtor", "Real eastate agent");
        realtor->add_money(200);
        add_actor(realtor, "floor0");
        // }}}
        // {{{ ranger @ main_street
        auto ranger = make_shared<Ranger>();
        add_actor(ranger, "main_street");
        // }}}

        auto hobo = make_shared<Actor>("hobo", "Friendly(?) hobo");
        add_actor(hobo, "shelter");

        auto bartender = make_shared<Actor>("bartender", "Bartender");
        bartender->observe("interacted", [this, bartender](shared_ptr<Entity> e) {
            talk(bartender, "Welcome to the bar!");
            talk(bartender, "Here you can buy a vast set of the finest products on the market.");
            talk(bartender, "We have both beer ($10) and juice ($50)! Something for everyone!");
            return true;
        });
        add_actor(bartender, "pub");

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

