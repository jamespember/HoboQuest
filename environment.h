#include <string>
#include <map>

namespace hoboquest {
	class Environment : Container {
		protected:
			string description;
			map<string, *Environment> neighbours;

		public:
			Environment(string n) : description(n) {}

			void on_enter(Actor *a);
			void on_exit(Actor *a);
			void on_drop(Item *a);
			void on_pickup(Item *a);
	};
}



