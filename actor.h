#ifndef HOBO_ACTOR
#define HOBO_ACTOR

#include <string>
#include <map>
#include "area.h"

namespace hoboquest {
	class Actor {
		protected:
			std::string name;
			Area *pos;
			int hp;

		public:
			Actor(std::string n, Area *p) : name(n), pos(p), hp(1) {}

			std::string name() const { return name; }
			int hp() const { return hp; }

			bool is_alive() const { return hp > 0; }

			bool go(Area *env) {
				pos->on_exit(this);
				env->on_enter(this);
				pos = env;
			}
	};
}

#endif
