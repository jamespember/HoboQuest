#ifndef HOBO_CONTAINER
#define HOBO_CONTAINER

#include <string>
#include <unordered_map>
#include "item.hpp"

namespace hoboquest {
	class Container {
		protected:
			std::unordered_map<std::string, Item> _items;

		public:
			Container() {}

			bool pickup(Item item) {
				_items.insert(item->name, item);
			}

			Item & has(std::string name) {
				return & *this->items.find(name);
			}

			Item drop(std::string name) {
				Item & it = has(name);
				if (it != NULL)
					items.erase(name);
				return it;
			}
	};
}

#endif
