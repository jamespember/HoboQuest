#include "equippable.hpp"
#include "item.hpp"

#include <string>

namespace hoboquest {
		Equippable::Equippable(std::string name) : Item(name) { }
		Equippable::Equippable(std::string name, unsigned value) : Item(name, value) { }
		Equippable::Equippable(std::string name, unsigned value, unsigned weight) :
		Item(name, value, weight) { }	
		
		const bool Equippable::is_equippable() 	const	{ return true; }
}

