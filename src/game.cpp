#include "game.hpp"

namespace hoboquest {
  Game::Game(std::istream &in_s, std::ostream &out_s) : in(in_s), out(out_s) {
    out << "HoboQuest starting...\n";
  }
}
