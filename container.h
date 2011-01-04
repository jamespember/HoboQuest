#include <string>
#include <map>
#include "item.h"

namespace hoboquest {
	class Container {
		map<string, *Item> items;

		bool pickup(Item a);
		Item & has(string name);
		Item & drop(string name);
	}
}
