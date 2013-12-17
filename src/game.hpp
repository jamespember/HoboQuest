#ifndef HOBO_GAME
#define HOBO_GAME

#include <iostream>
#include <string>
#include <vector>

// #include "container.hpp"
#include "area.hpp"
// #include "item.hpp"
// #include "actor.hpp"
// #include "player.hpp"

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
