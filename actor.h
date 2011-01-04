#include <string>
#include <map>
#include "environment.h"

namespace hoboquest {
	class Actor {
		protected:
			string name;
			int hp;
			Environment *pos;

		public:
			Actor(string n) : name(n), hp(1) {}

			string name() const { return name; }
			int hp() const { return hp; }

			bool is_alive() const { return hp > 0; }

			bool go(Environment *env) {
				pos->on_exit(this);
				env->on_enter(this);
				pos = env;
			}
	};
}



