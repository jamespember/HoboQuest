#ifndef HOBO_ITEM_EQUIPPABLE
#define HOBO_ITEM_EQUIPPABLE

#include <string>

#include "item.hpp"

namespace hoboquest {
	class Equippable : public Item {
		public:
			Equippable(std::string name);
			Equippable(std::string name, unsigned value);
			Equippable(std::string name, unsigned value, unsigned weight);

			const bool is_equippable() 	const;
	};
}

#endif
