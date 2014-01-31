#include "shop.hpp"

#include "actor/player.hpp"
#include "command/buy.hpp"

namespace hoboquest {

  Shop::Shop(const std::string &id, const std::string &name, Engine &engine) : 
  Area(id, name), _engine(engine) {
  }

  bool Shop::in_stock(const std::string &item_id) {
    return _stock.count(item_id) > 0;
  }

  void Shop::add_stock(std::shared_ptr<Item> item) {
    _stock[item->id()] = item;
    notify("added_stock", item);
  }

  std::shared_ptr<Item> Shop::get_stock(const std::string &item_id) {
    if (!in_stock(item_id))
      return nullptr;
    return _stock.at(item_id);
  }

  std::shared_ptr<Item> Shop::remove_stock(const std::string &item_id) {    
    auto item = get_stock(item_id);
    if (item != nullptr) {
      _stock.erase(item_id);
     notify("removed_stock", item);
    }
    return item;
  }

  int Shop::price(const std::string &item_id) {
    auto item = get_stock(item_id);
    if (item != nullptr) {
      return item->value();
    }
    return 0;
  }

  bool Shop::add_actor(std::shared_ptr<Actor> actor) {
    _engine.player->message("add_actor");
    if (actor == _engine.player) {
      printf("ADDING PLAYER!\n");
      _engine.player->commands.add_command(std::make_shared<BuyCommand>());
    }
    return Area::add_actor(actor);
  }

  void Shop::remove_actor(const std::string &id) {
    _engine.player->message("remove_actor");
    if (id == _engine.player->id()) {
      _engine.player->commands.remove_command("buy");
    }
    Area::remove_actor(id);
  }
}
