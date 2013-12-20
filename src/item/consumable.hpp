#ifndef HOBO_ITEM_CONSUMABLE
#define HOBO_ITEM_CONSUMABLE

#include <string>

#include "item.hpp"

namespace hoboquest {
	class Consumable : public Item {
		public:
			Consumable(std::string name);
			Consumable(std::string name, unsigned value);
			Consumable(std::string name, unsigned value, unsigned weight);

			const bool is_consumable() 	const;
	};
}

#endif
