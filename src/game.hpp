#ifndef HOBO_GAME
#define HOBO_GAME

#include <iostream>
#include <string>
#include <vector>

// #include "container.h"
// #include "area.h"
// #include "item.h"
// #include "actor.h"
// #include "player.h"

namespace hoboquest {
	class Game {
		protected:
			/*
			std::vector<*Area> areas;
			std::vector<*Item> items;
			std::vector<*Actor> actors;
			*/
			std::istream & in;
			std::ostream & out;

		public:
      Game(std::istream &in_s, std::ostream &out_s) : in(in_s), out(out_s) {
        out << "HoboQuest starting...\n";
      }
	};
}

#endif
