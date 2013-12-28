#ifndef HOBO_ITEM_CONSUMABLE
#define HOBO_ITEM_CONSUMABLE

#include <string>

#include "item.hpp"

namespace hoboquest {
  class Consumable : public Item {
    public:
      Consumable(std::string name, std::string description);

      virtual bool is_consumable() const;
  };
}

#endif
