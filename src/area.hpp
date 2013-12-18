#ifndef HOBO_AREA
#define HOBO_AREA

#include <iostream>
//#include <stdlib>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

// #include "container.h"
// #include "item.h"
// #include "actor.h"
// #include "player.h"

/*
Area: (string name, string description)
	Room
		PoliceHQ
		Bathroom
		Shop
	Outdoors
		Park
		Alley
*/

namespace hoboquest {
	class Area { // : public Container
		protected:
			std::string _name;
			std::string _description;
			std::unordered_map<std::string, std::shared_ptr<Area>> _exits;
			//vector _actors;
			//vector<shared_ptr<Item> _items;

		public:
      Area(std::string n, std::string desc) : _name(n), _description(desc) {
      	//_exits();
      	
        std::cout << "Name: " << _name << "\nDescription: " << _description << "\n";
      }
      
    	void add_exit(std::string direction, std::shared_ptr<Area> exit)  {
				_exits[direction] = exit;
    	}
    	
    	bool has_exit(std::string direction) {
    		return _exits.count(direction);
    	}
    	/*
    	bool remove_exit(std::string direction) {
    	
    	}*/
    /*
    getExit(name) -> Area
    removeExit(name) -> bool
    onEnter(actor, fromArea?)
    onLeave(actor, toArea?)
    */
	};
}

#endif
