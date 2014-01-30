#include "item.hpp"
#include "../entity.hpp"
#include "../actor/actor.hpp"

#include <memory>
#include <string>

namespace hoboquest {
  Item::Item(const std::string &id, const std::string &name) :
  Entity(ITEM, id, name) {
    _value = 1;
    _weight = 1;
  }

  unsigned Item::value() const { return _value; }
  unsigned Item::weight() const { return _weight; }

  void Item::set_value(unsigned value) {
    _value = value;
    notify("changed_value", shared_from_this());
  }
  void Item::set_weight(unsigned weight) {
    _weight = weight;
    notify("changed_weight", shared_from_this());
  }

  bool Item::is_consumable() const { return false; }
  bool Item::is_equippable() const { return false; }

  void Item::on_consume(std::shared_ptr<Actor> actor) {
    notify("consumed", actor);
  }
  void Item::on_equip(std::shared_ptr<Actor> actor) {
    notify("equipped", actor);
  }
  void Item::on_unequip(std::shared_ptr<Actor> actor) {
    notify("unequipped", actor);
  }

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
