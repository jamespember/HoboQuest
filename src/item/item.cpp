#include "item.hpp"

#include <string>

namespace hoboquest {
    Item::Item(std::string name) : Item(name, 1, 1) {}
    Item::Item(std::string name, unsigned value) : Item(name, value, 1) {}
    Item::Item(std::string name, unsigned value, unsigned weight) :
      _name(name), _value(value), _weight(weight) {}

    const std::string & Item::name()  const { return _name; }
    unsigned Item::value() const { return _value; }
    unsigned Item::weight() const { return _weight; }

    void Item::set_name(std::string name) { _name = name; }
    void Item::set_value(unsigned value) { _value = value; }
    void Item::set_weight(unsigned weight) { _weight = weight; }

    bool Item::is_consumable() const { return false; }
    bool Item::is_equippable() const { return false; }
    bool Item::is_container() const { return false; }
}
