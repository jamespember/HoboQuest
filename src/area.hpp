#ifndef HOBO_AREA
#define HOBO_AREA

#include <iostream>
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
      	std::cout << "Added area. ";
        std::cout << "Name: " << _name << "\nDescription: " << _description << "\n";
      }
      
      std::string get_name() const {
      	return this->_name;
      }
      
      std::string get_description() const {
      	return this->_description;
      }
      
      void set_name(const std::string name) {
      	this->_name = name;
      }
      
      void set_description(const std::string description) {
      	this->_description = description;
      }
      
    	void add_exit(const std::string &direction, std::shared_ptr<Area> exit)  {
				this->_exits[direction] = exit;
    	}
    	
    	bool has_exit(const std::string &direction) const {
    		return this->_exits.count(direction) > 0;
    	}
    	
    	std::shared_ptr<Area> get_exit(const std::string &direction) const {
    		if (!this->has_exit(direction))
    			return nullptr;
  			return this->_exits.at(direction);
    	}
    	
    	std::shared_ptr<Area> remove_exit(const std::string &direction) {
    		auto exit = this->get_exit(direction);
    		if (exit != nullptr)
    			this->_exits.erase(direction);
  			return exit;
    	}
    /*
    onEnter(actor, fromArea?)
    onLeave(actor, toArea?)
    */
	};
}

#endif
