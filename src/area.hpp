#ifndef HOBO_AREA
#define HOBO_AREA

#include <iostream>
#include <string>
#include <vector>

// #include "container.h"
// #include "area.h"
// #include "item.h"
// #include "actor.h"
// #include "player.h"

/*
Area: (string name, string description, map<string, *Area> exits, vector *actors, vector *items)
	Room
		PoliceHQ
		Bathroom
		Shop
	Outdoors
		Park
		Alley
  Methods:
    addExit(name, Area) -> bool
    getExit(name) -> Area
    hasExit(name) -> bool
    removeExit(name) -> bool
    onEnter(actor, fromArea?)
    onLeave(actor, toArea?)
*/

namespace hoboquest {
	class Area {
		protected:
			std::string _name;
			std::string _description;

		public:
      Area(std::string n, std::string desc) : _name(n), _description(desc) {
        //std::cout << "Name: " << _name << "\nDescription: " << _description << "\n";
      }
	};
}

#endif
