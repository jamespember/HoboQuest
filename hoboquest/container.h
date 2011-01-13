#ifndef HOBO_CONTAINER
#define HOBO_CONTAINER

#include <string>
#include <map>
#include "item.h"

using hoboquest::Item;

namespace hoboquest {

	class Container {
		protected:
			std::map<std::string, *Item> items;
		public:
			Container() { }
			bool pickup(std::string name, Item a) {
				items.insert(name, *a);
			}
			Item & has(std::string name) {
				return & *this->items.find(name);
			}
			Item & drop(std::string name) {
				Item & it = has(name);
				if (it != NULL)
					items.erase(name);
				return it;
			}
	};
}

#endif
