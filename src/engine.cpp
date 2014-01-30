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
    _entity_ptr = new Actor("dummy", "Dummy actor to demonstrate memory management");
  }

  Engine::~Engine() {
    delete _entity_ptr;
  }


  void Engine::connect_areas(const std::string &area_a, const std::string &dir_a,
      const std::string &dir_b, const std::string &area_b) {
    if (!areas.has(area_a) || !areas.has(area_b)) {
      _out << "Can't connect '" << area_a << "' with '" << area_b << "'\n";
      return;
    }

    auto a = areas.get(area_a), b = areas.get(area_b);
    a->add_exit(dir_a, b);
    b->add_exit(dir_b, a);
  }

  bool Engine::tick() {
    // Player interaction (stop game on false return value)
    if (!player->interact())
      return false;

    _out << "tick...\n";

    for (auto actor : actors.get_map())
      actor.second->tick();

    return true;
  }

  void Engine::loop() {
    while (tick());
  }


  void Engine::talk(std::shared_ptr<Actor> who, const std::string &what) const {
    player->out() << who->name() << " says: " << what << std::endl;
  }

  void Engine::import_entity(const std::unordered_map<std::string, std::string> &data) {
  }
} /* hoboquest */ 
