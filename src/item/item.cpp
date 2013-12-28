#include "item.hpp"

#include <string>

namespace hoboquest {
    Item::Item(std::string name, std::string description) : _name(name), _description(description) {
        _value = 1;
        _weight = 1;
    }

    const std::string & Item::name()  const { return _name; }
    const std::string & Item::description()  const { return _description; }
    unsigned Item::value() const { return _value; }
    unsigned Item::weight() const { return _weight; }

    void Item::set_name(std::string name) { _name = name; }
    void Item::set_description(std::string description) { _description = description; }
    void Item::set_value(unsigned value) { _value = value; }
    void Item::set_weight(unsigned weight) { _weight = weight; }

    bool Item::is_consumable() const { return false; }
    bool Item::is_equippable() const { return false; }
    bool Item::is_container() const { return false; }
}
