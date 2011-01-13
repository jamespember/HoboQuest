#ifndef HOBO_GAME
#define HOBO_GAME

#include <iostream>
#include <string>
#include <vector>

#include "container.h"
#include "area.h"
#include "item.h"
#include "actor.h"
#include "player.h"

using std::ostream;
using std::istream;

namespace hoboquest {
	class Game {
		protected:
			/*
			std::vector<*Area> areas;
			std::vector<*Item> items;
			std::vector<*Actor> actors;
			*/
			istream in;
			ostream out;

		public:
			Game(istream in_s, ostream out_s) {
				in = in_s;
				out = out_s;

				out << "HoboQuest starting up\n";
			}
	};
}

#endif
