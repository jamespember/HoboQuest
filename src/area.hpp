#ifndef HOBO_AREA
#define HOBO_AREA

#include "container_entity.hpp"
#include "actor.hpp"
#include "util/ptr_map.hpp"

#include <string>
#include <memory>
#include <unordered_map>

namespace hoboquest {

	class Actor;

	class Area : public ContainerEntity {
		protected:
			PtrMap<Actor> _actors;
			std::string _description;
			std::unordered_map<std::string, std::shared_ptr<Area>> _exits;

		public:
      Area(const std::string &id, const std::string &name);
      
      std::string description() const;      
      void set_description(const std::string description);
      
    	void add_exit(const std::string &direction, std::shared_ptr<Area> exit);
    	bool has_exit(const std::string &direction) const;
    	std::shared_ptr<Area> get_exit(const std::string &direction) const;
    	std::shared_ptr<Area> remove_exit(const std::string &direction);

			bool add_actor(std::shared_ptr<Actor> actor);
			bool has_actor(const std::string &id) const;
      std::shared_ptr<Actor> get_actor(const std::string &id) const;
      void remove_actor(const std::string &id);
  };
}

#endif
