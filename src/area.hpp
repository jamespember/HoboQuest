#ifndef HOBO_AREA
#define HOBO_AREA

#include <string>
#include <memory>
#include <unordered_map>

#include "actor.hpp"

namespace hoboquest {

	class Actor;

	class Area { // : public Container
		protected:
			std::string _name;
			std::string _description;
			std::unordered_map<std::string, std::shared_ptr<Area>> _exits;
			std::unordered_map<std::string, std::shared_ptr<Actor>> _actors;
			//vector<shared_ptr<Item> _items;
		public:
      Area(std::string n, std::string desc);
      
      std::string get_name() const;
      std::string get_description() const;      
      void set_name(const std::string name);
      void set_description(const std::string description);
      
    	void add_exit(const std::string &direction, std::shared_ptr<Area> exit);
    	bool has_exit(const std::string &direction) const;
    	std::shared_ptr<Area> get_exit(const std::string &direction) const;
    	std::shared_ptr<Area> remove_exit(const std::string &direction);
    	
    	void add_actor(std::shared_ptr<Actor> actor);
    	bool has_actor(const std::string &name) const;
    	std::shared_ptr<Actor> get_actor(const std::string &name) const;
    	std::shared_ptr<Actor> remove_actor(const std::string &name);
	};
}

#endif
