#ifndef HOBO_GAME
#define HOBO_GAME

#include <iostream>
#include <string>
#include <vector>

#include "area.hpp"
#include "item/item.hpp"
#include "actor.hpp"
#include "player.hpp"

template <typename T> using ptr_vector = std::vector<std::shared_ptr<T>>;

namespace hoboquest {
  class Game {
    protected:
      std::shared_ptr<Player> _player;
      ptr_vector<Area> _areas;
      ptr_vector<Actor> _actors;
      ptr_vector<Item> _items;

      std::istream & _in;
      std::ostream & _out;

    public:
      Game(std::istream &in_s, std::ostream &out_s);

      std::vector<std::string> read_command();
      void tick();
      void loop();
  };
}

#endif
