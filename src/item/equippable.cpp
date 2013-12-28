#include "equippable.hpp"
#include "item.hpp"

#include <string>

namespace hoboquest {
    Equippable::Equippable(std::string name, std::string description) :
      Item(name, description) { }

    bool Equippable::is_equippable() const { return true; }
}

