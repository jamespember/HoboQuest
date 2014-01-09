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
  }

  bool Game::tick() {
    _out << "tick...\n";

    // Player interaction (stop game on false return value)
    if (!_player->interact())
      return false;

    _out << "Running actor actions\n";
    for (auto actor : _actors)
      actor->tick();

    return true;
  }

  void Game::loop() {
    while (tick());
  }
} /* hoboquest */ 
