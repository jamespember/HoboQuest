#include <string>
#include <map>
#include "item.h"

namespace hoboquest {
	class Container {
		protected:
			std::map<std::string, *Item> items;

		public:
			bool pickup(Item a);
			Item & has(std::string name);
			Item & drop(std::string name);
	};
}
