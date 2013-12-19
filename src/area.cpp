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

    Area::Area(std::string n, std::string desc) : _name(n), _description(desc) {
    	std::cout << "Added area. ";
      std::cout << "Name: " << _name << "\nDescription: " << _description << "\n";
    }
    
    std::string Area::get_name() const {
    	return this->_name;
    }
    
    std::string Area::get_description() const {
    	return this->_description;
    }
    
    void Area::set_name(const std::string name) {
    	this->_name = name;
    }
    
    void Area::set_description(const std::string description) {
    	this->_description = description;
    }
    
  	void Area::add_exit(const std::string &direction, std::shared_ptr<Area> exit)  {
			this->_exits[direction] = exit;
  	}
  	
  	bool Area::has_exit(const std::string &direction) const {
  		return this->_exits.count(direction) > 0;
  	}
  	
  	std::shared_ptr<Area> Area::get_exit(const std::string &direction) const {
  		if (!this->has_exit(direction))
  			return nullptr;
			return this->_exits.at(direction);
  	}
  	
  	std::shared_ptr<Area> Area::remove_exit(const std::string &direction) {
  		auto exit = this->get_exit(direction);
  		if (exit != nullptr)
  			this->_exits.erase(direction);
			return exit;
  	}
  	
  	void Area::add_actor(std::shared_ptr<Actor> actor)  {
			this->_actors[actor->get_name()] = actor;
  	}
  	
  	bool Area::has_actor(const std::string &name) const {
  		return this->_actors.count(name) > 0;
  	}
  	
  	std::shared_ptr<Actor> Area::get_actor(const std::string &name) const {
  		if (!this->has_actor(name))
  			return nullptr;
			return this->_actors.at(name);
  	}
  	
  	std::shared_ptr<Actor> Area::remove_actor(const std::string &name) {
  		auto actor = this->get_actor(name);
  		if (actor != nullptr)
  			this->_actors.erase(name);
			return actor;
  	}    

  /*
  onEnter(actor, fromArea?)
  onLeave(actor, toArea?)
  */
}
