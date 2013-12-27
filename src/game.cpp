#include "game.hpp"

#define DEBUGGING 1
#include "util/debug.hpp"

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
    this->_out << "HoboQuest starting...\n";
    this->_player = std::make_shared<Player>(*this, in, out);
    this->loop();
  }

  void Game::tick() {
    DEBUG("tick...");
  }

  void Game::loop() {
    while (1) {
      if (!this->_player->interact())
        return;
      this->tick();
    }
  }
} /* hoboquest */ 
