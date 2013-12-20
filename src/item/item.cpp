#include "item.hpp"

#include <string>

namespace hoboquest {
		Item::Item(std::string name) : Item(name, 1, 1) {}
		Item::Item(std::string name, unsigned value) : Item(name, value, 1) {}
		Item::Item(std::string name, unsigned value, unsigned weight) :
      _name(name), _type(Item::Type::Equippable), _value(value), _weight(weight) {}


		const Item::Type & Item::type()		const { return this->_type; }
		const std::string & Item::name()	const { return this->_name; }
		unsigned Item::value()						const { return this->_value; }
		unsigned Item::weight()						const { return this->_weight; }
		
		const bool Item::is_consumable() 	const	{ return false; }
		const bool Item::is_equippable() 	const	{ return false; }
		const bool Item::is_container()  	const	{ return false; }
}
