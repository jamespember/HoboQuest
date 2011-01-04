#include <string>
#include <map>

namespace hoboquest {
	class Area : Container {
		protected:
			std::string description;
			std::map<std::string, *Area> neighbours;

		public:
			Area(std::string n) : description(n) {}

			void on_enter(Actor *a);
			void on_exit(Actor *a);
			void on_drop(Item *a);
			void on_pickup(Item *a);
	};
}

