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
  Actor(id, name), _idle_turns(2) {
    srand(time(NULL));
  }

  unsigned Walker::random_choice(unsigned min, unsigned max) const {
    return min + (int)((double)rand() / RAND_MAX * (max-min+1));
  }

  void Walker::random_move() {
    if (!_location) return;

    auto &areas = _location->exits();
    if (areas.empty()) return;

    auto it = areas.begin();
    unsigned x = random_choice(0, areas.size() - 1);
    
    std::advance(it, x);
    std::string exit = (*it).first;
    std::string target = (*it).second->id();
    go(exit);

    _turns_to_move = _idle_turns;
  }

  void Walker::tick() {
    if (_turns_to_move-- < 1)
      random_move();
    Actor::tick();
  }
} /* hoboquest */ 

