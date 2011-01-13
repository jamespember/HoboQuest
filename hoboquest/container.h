#ifndef HOBO_CONTAINER
#define HOBO_CONTAINER

#include <string>
#include <map>
//#include "item.h"



namespace hoboquest {
	struct Item {
		
	};

	class Container {
		protected:
			std::map<std::string, Item> items;
		public:
			bool pickup(Item a);
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
