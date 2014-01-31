#include "walker.hpp"
#include "actor.hpp"
#include "player.hpp"

#include <memory>
#include <iterator>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>

namespace hoboquest {
  Walker::Walker(const std::string &id, const std::string &name) :
  Actor(id, name), _spoken_with_player(false), _turns_stationary(0) {
    _hp = _hp_max = 30;
    _damage = 10;

    srand(time(NULL));

    observe("interacted", [this](std::shared_ptr<Entity> e) {
      auto player = std::dynamic_pointer_cast<Player>(e);
      if (!player) return false;
      player->listen(shared_from_this(), "Howdy friend!");
      return true;
    });
  }

  Walker::~Walker() {}

  unsigned Walker::random_choice(unsigned min, unsigned max) const {
    return min + (int)((double)rand() / RAND_MAX * (max-min+1));
  }

  void Walker::random_move() {
    if (!_location) return;

    auto &areas = _location->exits();
    if (areas.empty()) return;

    auto it = areas.begin();
    unsigned x = random_choice(0, areas.size());
    
    if (x < areas.size()) {
      std::advance(it, x);
      std::string exit = (*it).first;
      std::string target = (*it).second->id();
      go(exit);
      _turns_stationary = 0;
    }
  }

  void Walker::tick() {
    if (!_location) return;

    if (_location->has_actor("player")) {
      auto player = std::dynamic_pointer_cast<Player>(_location->get_actor("player"));
      if (!_spoken_with_player) {
        player->listen(shared_from_this(), "Hey there fella! Don't cause any trouble or I'll come after you.");
        _spoken_with_player = true;
      }

      if (player->has_item("gun"))
        player->listen(shared_from_this(), "Don't go about waving that gun around mister!");
    }

    if (_turns_stationary++ > 2)
      random_move();

    Actor::tick();
  }
} /* hoboquest */ 

