#ifndef HOBO_AREA_SHOP
#define HOBO_AREA_SHOP

#include "area.hpp"
#include "engine.hpp"

#include <string>
#include <unordered_map>

namespace hoboquest {
  class BuyCommand;
  
	class Shop : public Area {
		protected:
      Engine &_engine;
      std::unordered_map<std::string, std::shared_ptr<Item>> _stock;
      std::shared_ptr<BuyCommand> _command;

		public:
      Shop(const std::string &id, const std::string &name, Engine &engine);

      bool in_stock(const std::string &item_id);
      void add_stock(std::shared_ptr<Item> item);
      std::shared_ptr<Item> get_stock(const std::string &item_id);
      std::shared_ptr<Item> remove_stock(const std::string &item_id);
      int price(const std::string &item_id);
      
      virtual bool add_actor(std::shared_ptr<Actor> actor);
      virtual void remove_actor(const std::string &id);

  };
}

#endif
