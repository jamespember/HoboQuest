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
  unsigned Walker::randomChoice(unsigned min, unsigned max) const {
    return min + (int)((double)rand() / RAND_MAX * (max-min+1));
  }

  Walker::Walker(const std::string &id, const std::string &name) :
  Actor(id, name) {
    srand(time(NULL));
  }

  Walker::~Walker() {}

  void Walker::tick() {
    if (!_location)
      return;

    std::cout << "Walker currently located at " << _location->id() << std::endl;

    auto &areas = _location->exits();
    if (areas.empty())
      return;

    std::cout << "Number of exits: "<< areas.size() << std::endl;

    auto it = areas.begin();
    unsigned x = randomChoice(0, areas.size() * 2);
    
    if (x < areas.size()) {
      std::advance(it, x);
      std::string exit = (*it).first;
      std::string target = (*it).second->id();
      std::cout << "x=" << x << ", chose " << exit << " which leads to " << target << std::endl;
      go(exit);
    }
  }

  void Walker::on_interact(std::shared_ptr<Actor> actor) {
    auto player = std::dynamic_pointer_cast<Player>(actor);
    if (!player) return;
    player->out() << name() << " says: Howdy friend!" << std::endl;
  }
} /* hoboquest */ 
