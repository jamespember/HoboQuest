#ifndef HOBO_ITEM
#define HOBO_ITEM

#include "../entity.hpp"

#include <string>

namespace hoboquest {
  class Item : public Entity {
    protected:
      std::string _description;
      unsigned _value, _weight;

    public:
      Item(const std::string &id, const std::string &name);

      const std::string & description() const;
      unsigned value() const;
      unsigned weight() const;

      void set_description(std::string description);
      void set_value(unsigned value);
      void set_weight(unsigned weight);

      virtual bool is_consumable() const;
      virtual bool is_equippable() const;
      virtual bool is_container() const;
  };
}

#endif
