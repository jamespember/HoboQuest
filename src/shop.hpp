#ifndef HOBO_AREA_SHOP
#define HOBO_AREA_SHOP

#include "area.hpp"
#include "engine.hpp"

#include <string>

namespace hoboquest {
  
	class Shop : public Area {
		protected:
      Engine &_engine;

		public:
      Shop(const std::string &id, const std::string &name, Engine &engine);

      bool in_stock(const std::string &item_id);
      int price(const std::string &item_id);

      bool add_actor(std::shared_ptr<Actor> actor);
      void remove_actor(const std::string &id);

  };
}

#endif
