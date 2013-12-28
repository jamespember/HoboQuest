#include "area.hpp"

#include <iostream>

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

    Area::Area(std::string n, std::string desc) : _name(n), _description(desc) { }
    
    std::string Area::name() const 							{ return _name; }
    std::string Area::description() const 			{ return _description; }
    void Area::set_name(const std::string name) {	_name = name; }
    void Area::set_description(const std::string description) { 
    	_description = description;
    }
    
  	void Area::add_exit(const std::string &direction, std::shared_ptr<Area> exit)  {
			_exits[direction] = exit;
  	}
  	
  	bool Area::has_exit(const std::string &direction) const {
  		return _exits.count(direction) > 0;
  	}
  	
  	std::shared_ptr<Area> Area::get_exit(const std::string &direction) const {
  		if (!has_exit(direction))
  			return nullptr;
			return _exits.at(direction);
  	}
  	
  	std::shared_ptr<Area> Area::remove_exit(const std::string &direction) {
  		auto exit = get_exit(direction);
  		if (exit != nullptr)
  			_exits.erase(direction);
			return exit;
  	}
  	
  	void Area::add_actor(std::shared_ptr<Actor> actor)  {
			_actors[actor->name()] = actor;
  	}
  	
  	bool Area::has_actor(const std::string &name) const {
  		return _actors.count(name) > 0;
  	}
  	
  	std::shared_ptr<Actor> Area::get_actor(const std::string &name) const {
  		if (!has_actor(name))
  			return nullptr;
			return _actors.at(name);
  	}
  	
  	std::shared_ptr<Actor> Area::remove_actor(const std::string &name) {
  		auto actor = get_actor(name);
  		if (actor != nullptr)
  			_actors.erase(name);
			return actor;
  	}    

  /*
  onEnter(actor, fromArea?)
  onLeave(actor, toArea?)
  */
}
