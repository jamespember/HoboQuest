#include <string>
#include <map>
#include "environment.h"

namespace hoboquest {
	class Actor {
		protected:
			std::string name;
			Environment *pos;
			int hp;

		public:
			Actor(std::string n, Environment *p) : name(n), pos(p), hp(1) {}

			std::string name() const { return name; }
			int hp() const { return hp; }

			bool is_alive() const { return hp > 0; }

			bool go(Environment *env) {
				pos->on_exit(this);
				env->on_enter(this);
				pos = env;
				return false; //TODO
			}

			bool pick_up(Item *a) {
				return false; //TODO
			}
			bool drop(Item *a) {
				return false; //TODO
			}
	};
}

