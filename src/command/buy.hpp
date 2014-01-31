#ifndef HOBO_BUY_COMMAND
#define HOBO_BUY_COMMAND

#include "command.hpp"
#include "../actor/player.hpp"
#include "../shop.hpp"

#include <deque>
#include <string>

namespace hoboquest {

  class Shop;

  class BuyCommand : public Command {
    public:
      BuyCommand() : Command("buy") {}

      CommandOutcome execute(Player &player, std::deque<std::string> &args) {
        if (args.empty())
          return player.message("Buy what?"), ERROR;
        auto item_id = args.front();
        
        std::shared_ptr<Shop> shop = std::dynamic_pointer_cast<Shop>(player.location());
        if (!shop) return ERROR;

        if (!shop->in_stock(item_id))
          return player.message("Sorry, we're out."), NOOP;      
        
        int price = shop->price(item_id);
        if (player.money() < price)
          return player.message("Not enough money!"), NOOP;

        auto item = shop->stock_remove(item_id);
        if (item == nullptr)
          return player.message("Sorry, that is bug infested."), ERROR;

        player.remove_money(price);
        player.message("Here you are!");
        player.add_item(item);
        return SUCCESS;
      }
  };
} /* hoboquest */ 

#endif
