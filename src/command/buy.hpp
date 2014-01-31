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
        
        //std::shared_ptr<Area> area =
        std::shared_ptr<Shop> shop = std::dynamic_pointer_cast<Shop>(player.location());
        if (!shop) return ERROR;

        if (!shop->in_stock(item_id))
          return player.message("Sorry, we're out."), NOOP;      
        
        int price = shop->price(item_id);
        if (player.money() < price)
          return player.message("Not enough money!"), NOOP;
        player.remove_money(price);

        player.message("YES SIR!");
        /*
        if (!item) {
          player.out() << "You don't carry any item called '" << args.front() << "'\n";
          return ERROR;
        }

        if (player.consume(args.front())) {
          player.out() << "You consume " << *item << std::endl; 
          return SUCCESS;
        }

        player.out() << "'" << args.front() << "' can't be consumed\n";
        return ERROR;
        */
        return SUCCESS;
      }
  };
} /* hoboquest */ 

#endif
