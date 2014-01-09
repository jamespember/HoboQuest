#include "engine.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "area.hpp"
#include "item/item.hpp"
#include "actor.hpp"
#include "player.hpp"

namespace hoboquest {
  Engine::Engine(std::istream &in, std::ostream &out) :
  _in(in), _out(out) {
    player = std::make_shared<Player>(in, out);
  }

  bool Engine::tick() {
    _out << "tick...\n";

    // Player interaction (stop game on false return value)
    if (!player->interact())
      return false;

    _out << "Running actor actions\n";
    for (auto actor : actors.get_map())
      actor.second->tick();

    return true;
  }

  void Engine::loop() {
    while (tick());
  }

  void Engine::import_entity(const std::unordered_map<std::string, std::string> &data) {
  }
} /* hoboquest */ 
