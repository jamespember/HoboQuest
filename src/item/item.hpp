#ifndef HOBO_ITEM
#define HOBO_ITEM

#include <string>

namespace hoboquest {
  class Item {
    protected:
      std::string _name, _description;
      unsigned _value, _weight;

    public:
      Item(std::string name, std::string description);

      const std::string & name() const;
      const std::string & description() const;
      unsigned value() const;
      unsigned weight() const;

      void set_name(std::string name);
      void set_description(std::string description);
      void set_value(unsigned value);
      void set_weight(unsigned weight);

      virtual bool is_consumable() const;
      virtual bool is_equippable() const;
      virtual bool is_container() const;
  };
}

#endif
