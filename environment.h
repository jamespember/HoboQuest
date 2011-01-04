#include <string>
#include <map>
#include "container.h"

namespace hoboquest {
	class Environment : Container {
		protected:
			std::string description;
			std::map<std::string, *Environment> neighbours;

		public:
			Environment(std::string n) : description(n) {}

			void on_enter(Actor *a);
			void on_exit(Actor *a);
			void on_drop(Item *a);
			void on_pickup(Item *a);
	};
}



