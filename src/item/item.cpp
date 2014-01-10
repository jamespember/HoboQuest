#include "item.hpp"

#include <string>

namespace hoboquest {
  Item::Item(const std::string &id, const std::string &name) :
  Entity(ITEM, id, name) {
    _value = 1;
    _weight = 1;
  }

  unsigned Item::value() const { return _value; }
  unsigned Item::weight() const { return _weight; }

  void Item::set_value(unsigned value) { _value = value; }
  void Item::set_weight(unsigned weight) { _weight = weight; }

  bool Item::is_consumable() const { return false; }
  bool Item::is_equippable() const { return false; }

  void Item::on_consume(Actor &actor) {}
  void Item::on_equip(Actor &actor) {}

  void Item::describe(std::ostream &out) const {
    Entity::describe(out);
    out << "  ";
    if (is_equippable())
      out << "equippable, ";
    if (is_consumable())
      out << "consumable, ";
    out << "value: " << _value << ", weight: " << _weight << std::endl;
  }
}
