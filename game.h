#include <string>
#include <vector>

#include "container.h"
#include "area.h"
#include "item.h"
#include "actor.h"
#include "player.h"

namespace hoboquest {
	class Hoboquest {
		protected:
			std::vector<*Area> areas;
			std::vector<*Item> items;
			std::vector<*Actor> actors;
	};
}
