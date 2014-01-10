#ifndef HOBO_ITEM
#define HOBO_ITEM

#include "../entity.hpp"

#include <string>

namespace hoboquest {
  class Actor;

  class Item : public Entity {
    protected:
      unsigned _value, _weight;

    public:
      Item(const std::string &id, const std::string &name);

      unsigned value() const;
      unsigned weight() const;

      void set_value(unsigned value);
      void set_weight(unsigned weight);

      virtual bool is_consumable() const;
      virtual bool is_equippable() const;

      virtual void on_consume(Actor &actor);
      virtual void on_equip(Actor &actor);

      virtual void describe(std::ostream &out) const;
  };
}

#endif
