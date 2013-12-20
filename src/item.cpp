#include "item.hpp"

#include <string>

namespace hoboquest {
		Item::Item(std::string name, unsigned value, unsigned weight) :
      _name(name), _type("item"), _value(value), _weight(weight) {}

		Item::Item(std::string name, unsigned value) :
      Item(name, value, 1) {}

		Item::Item(std::string name) :
      Item(name, 1, 1) {}

		const std::string & Item::type() const { return this->_type; }
		const std::string & Item::name() const { return this->_name; }
		unsigned Item::value() const { return this->_value; }
		unsigned Item::weight() const { return this->_weight; }
}
