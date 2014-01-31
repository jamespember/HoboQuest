#ifndef HOBO_AREA_SHOP
#define HOBO_AREA_SHOP

#include "area.hpp"
#include "engine.hpp"

#include <string>
#include <unordered_map>

namespace hoboquest {
  
	class Shop : public Area {
		protected:
      Engine &_engine;
      std::unordered_map<std::string, std::shared_ptr<Item>> _stock;

		public:
      Shop(const std::string &id, const std::string &name, Engine &engine);

      bool in_stock(const std::string &item_id);
      void stock_add(std::shared_ptr<Item> item);
      std::shared_ptr<Item> stock_get(const std::string &item_id);
      std::shared_ptr<Item> stock_remove(const std::string &item_id);
      int price(const std::string &item_id);
      
      bool add_actor(std::shared_ptr<Actor> actor);
      void remove_actor(const std::string &id);

  };
}

#endif
