#include "game.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "area.hpp"
#include "item/item.hpp"
#include "actor.hpp"
#include "player.hpp"

namespace hoboquest {
  Game::Game(std::istream &in, std::ostream &out) :
  _in(in), _out(out) {
    _out << "HoboQuest starting...\n";
    _player = std::make_shared<Player>(in, out);
    loop();
  }

  void Game::tick() {
    _out << "tick...\n";
  }

  void Game::loop() {
    while (1) {
      if (!_player->interact())
        return;
      tick();
    }
  }
} /* hoboquest */ 
