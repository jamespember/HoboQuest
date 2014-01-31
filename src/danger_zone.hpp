#ifndef HOBO_AREA_DANGER_ZONE
#define HOBO_AREA_DANGER_ZONE

#include "area.hpp"
#include "actor/player.hpp"

#include <string>

namespace hoboquest {
  
	class DangerZone : public Area {
		protected:
      const int _hp_mod;

		public:
      DangerZone(const std::string &id, const std::string &name, const int hp_mod) :
      Area(id, name), _hp_mod(hp_mod)   {}
      
      bool add_actor(std::shared_ptr<Actor> actor) {
        actor->modify_hp(_hp_mod);
        return Area::add_actor(actor);
      }
  };
}

#endif
