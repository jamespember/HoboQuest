#ifndef HOBO_GAME
#define HOBO_GAME

#include "../engine.hpp"
#include "../item/consumable.hpp"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace hoboquest {
  class Game : public Engine {
    public:
      Game(std::istream &in, std::ostream &out) : Engine(in, out) {
        _out << "Starting HoboQuest...\n";

        auto alley = make_shared<Area>("Alley",
            "Starting area.");
        auto main_street = make_shared<Area>("Main street",
            "The main street of the town, plenty of places to go from here.");
        auto market = make_shared<Area>("Market",
            "The town market, there's not many people around right now though.");
        auto pub = make_shared<Area>("Pub",
            "A pub filled with people, more or less drunk.");
        auto shelter = make_shared<Area>("Homeless shelter",
            "A state-owned homeless shelter for people lacking a home.");
        auto park = make_shared<Area>("Park",
            "A park with plenty of park benches.");
        auto police_station = make_shared<Area>("Police station",
            "The town police station.");
        auto cell = make_shared<Area>("Jail cell",
            "A jail cell inside the police station.");
        auto floor0 = make_shared<Area>("Apartments, bottom floor",
            "Bottom floor of a large apartments building.");
        auto floor1 = make_shared<Area>("Apartments, 1st floor",
            "Hallway on the first floor of the aparments building.");
        auto floor2 = make_shared<Area>("Apartments, 2nd floor",
            "Hallway on the second floor of the aparments building.");
        auto roof = make_shared<Area>("Roof",
            "The rooftop area of a a large apartments building.");

        /*
           Roof
            |
          Floor2
            |
          Floor1
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
        main_street->add_exit("west", alley);
        alley->add_exit("east", main_street);
        alley->add_exit("north", pub);
        pub->add_exit("south", alley);

        main_street->add_exit("east", shelter);
        shelter->add_exit("west", main_street);

        main_street->add_exit("south", police_station);
        police_station->add_exit("north", main_street);
        police_station->add_exit("west", cell);
        cell->add_exit("east", police_station);

        main_street->add_exit("north", market);
        market->add_exit("south", main_street);

        market->add_exit("east", park);
        park->add_exit("west", market);

        market->add_exit("west", floor0);
        floor0->add_exit("east", market);
        floor0->add_exit("up", floor1);
        floor1->add_exit("up", floor2);
        floor2->add_exit("up", roof);
        floor1->add_exit("down", floor0);
        floor2->add_exit("down", floor1);
        roof->add_exit("down", floor2);
        roof->add_exit("east", market); // jump

        // Items
        auto beer = make_shared<Consumable>("Beer", "A lovely beverage");
      }
  };
}

#endif
