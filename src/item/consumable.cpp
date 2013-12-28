#include "consumable.hpp"
#include "item.hpp"

#include <string>

namespace hoboquest {
  Consumable::Consumable(std::string name, std::string description) : Item(name, description) { }
  
  bool Consumable::is_consumable() const { return true; }
}

