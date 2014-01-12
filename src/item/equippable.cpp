#include "equippable.hpp"
#include "item.hpp"
#include "../actor.hpp"

#include <string>

namespace hoboquest {
    Equippable::Equippable(std::string name, std::string description) :
      Item(name, description) { }

    bool Equippable::is_equippable() const { return true; }
    void Equippable::on_equip(std::shared_ptr<Actor> actor) {}
}

