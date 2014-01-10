#include "consumable.hpp"
#include "item.hpp"
#include "../actor.hpp"

#include <string>

namespace hoboquest {

  Consumable::Consumable(std::string name, std::string description) :
    Item(name, description), _hp_modifier(0) {}
  
  bool Consumable::is_consumable() const { return true; }

  void Consumable::on_consume(Actor &actor) {
    actor.modify_hp(_hp_modifier);
  }

  int Consumable::hp_modifier() const { return _hp_modifier; }
  void Consumable::set_hp_modifier(int modifier) { _hp_modifier = modifier; }

}

