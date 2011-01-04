#ifndef HOBO_PLAYER
#define HOBO_PLAYER

#include <string>
#include <map>
#include "actor.h"
#include "item.h"

namespace hoboquest {
	class Player : public Actor {
		public:
			Player(std::string n, Area *p) : hp(100) {} 

			bool use(Item *a) {
			}
	};
}

#endif
