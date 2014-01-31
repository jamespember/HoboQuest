#include "shop.hpp"

#include "actor/player.hpp"
#include "command/buy.hpp"

namespace hoboquest {
  class Engine;
  class Player;
  class BuyCommand;

  Shop::Shop(const std::string &id, const std::string &name, Engine &engine) : 
    Area(id, name), _engine(engine) {
  }

  bool Shop::in_stock(const std::string &item_id) {
    return true;
  }

  int Shop::price(const std::string &item_id) {
    return 10;
  }

  bool Shop::add_actor(std::shared_ptr<Actor> actor) {
    if (actor == _engine.player) {
      _engine.player->commands.add_command(std::make_shared<BuyCommand>());
    }
    return Area::add_actor(actor);
  }

  void Shop::remove_actor(const std::string &id) {
    if (id == _engine.player->id()) {
      _engine.player->commands.remove_command("buy");
    }
    Area::remove_actor(id);
  }
}
