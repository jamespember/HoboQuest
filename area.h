#ifndef HOBO_AREA
#define HOBO_AREA

#include <string>
#include <map>
#include "container.h"

namespace hoboquest {
	class Area : public Container {
		protected:
			std::string description;
			std::map<std::string, *Area> neighbours;

		public:
			Area(std::string n) : description(n) {}

			void on_enter(Actor *a) {}
			void on_exit(Actor *a) {}
			void on_drop(Item *a) {}
			void on_pickup(Item *a) {}
	};
}

#endif