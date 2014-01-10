#include "item.hpp"

#include <string>

namespace hoboquest {
  Item::Item(const std::string &id, const std::string &name) :
  Entity(ITEM, id, name) {
    _value = 1;
    _weight = 1;
  }

  const std::string & Item::description()  const { return _description; }
  unsigned Item::value() const { return _value; }
  unsigned Item::weight() const { return _weight; }

  void Item::set_description(std::string description) { _description = description; }
  void Item::set_value(unsigned value) { _value = value; }
  void Item::set_weight(unsigned weight) { _weight = weight; }

  bool Item::is_consumable() const { return false; }
  bool Item::is_equippable() const { return false; }

  void Item::on_consume(Actor &actor) {}
  void Item::on_equip(Actor &actor) {}
}
