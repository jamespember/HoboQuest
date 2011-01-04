#include <string>
#include <map>
#include "item.h"

namespace hoboquest {
	class Container {
		protected:
			map<string, *Item> items;

		public:
			bool pickup(Item a);
			Item & has(string name);
			Item & drop(string name);
	};
}
