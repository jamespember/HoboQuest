#ifndef HOBO_ENGINE
#define HOBO_ENGINE

#include <iostream>
#include <string>
#include <deque>

#include "area.hpp"
#include "util/ptr_map.hpp"
#include "item/item.hpp"
#include "actor.hpp"

namespace hoboquest {
  class Player;

  class Engine {
    protected:
      std::istream & _in;
      std::ostream & _out;
      Entity *_entity_ptr;

    public:
      PtrMap<Area> areas;
      PtrMap<Item> items;
      PtrMap<Actor> actors;
      std::shared_ptr<Player> player;

      Engine(std::istream &in_s, std::ostream &out_s);

      virtual ~Engine();

      std::deque<std::string> read_command();
      bool tick();
      void loop();

      void import_entity(const std::unordered_map<std::string, std::string> &data);
  };
}

#endif
