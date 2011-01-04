#include <string>
#include <map>
#include "actor.h"
#include "item.h"

namespace hoboquest {
	class Player : Actor {
		public:
			Player(Environment *p) : name("player"), pos(p), hp(100) {} 

			bool use(Item *a) {
				return false; //TODO
			}
	};
}
