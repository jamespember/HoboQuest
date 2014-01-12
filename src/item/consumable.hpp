#ifndef HOBO_ITEM_CONSUMABLE
#define HOBO_ITEM_CONSUMABLE

#include "item.hpp"

#include <string>

namespace hoboquest {
  class Actor;

  class Consumable : public Item {
    protected:
      int _hp_modifier;

    public:
      Consumable(std::string name, std::string description);

      bool is_consumable() const;
      virtual void on_consume(std::shared_ptr<Actor> actor);

      int hp_modifier() const;
      void set_hp_modifier(int modifier);
  };
}

#endif
