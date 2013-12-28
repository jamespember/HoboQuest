#ifndef HOBO_ITEM
#define HOBO_ITEM

#include <string>

namespace hoboquest {
  class Item {
    protected:
      std::string _name;
      unsigned _value, _weight;

    public:
      Item(std::string name);
      Item(std::string name, unsigned value);
      Item(std::string name, unsigned value, unsigned weight);

      const std::string & name() const;
      unsigned value() const;
      unsigned weight() const;

      void set_name(std::string name);
      void set_value(unsigned value);
      void set_weight(unsigned weight);

      virtual bool is_consumable() const;
      virtual bool is_equippable() const;
      virtual bool is_container() const;
  };
}

#endif
