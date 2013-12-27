#include "consumable.hpp"
#include "item.hpp"

#include <string>

namespace hoboquest {
  Consumable::Consumable(std::string name) : Item(name) { }
  Consumable::Consumable(std::string name, unsigned value) : Item(name, value) { }
  Consumable::Consumable(std::string name, unsigned value, unsigned weight) :
    Item(name, value, weight) { }

  bool Consumable::is_consumable() const { return true; }
}

