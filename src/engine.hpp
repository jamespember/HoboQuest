#ifndef HOBO_ENGINE
#define HOBO_ENGINE

#include <iostream>
#include <string>
#include <deque>

#include "area.hpp"
#include "util/ptr_map.hpp"
#include "item/item.hpp"
#include "actor/actor.hpp"

namespace hoboquest {
  class Player;

  class Engine {
    protected:
      std::istream & _in;
      std::ostream & _out;
      Entity *_entity_ptr;
      bool _quitting;

    public:
      PtrMap<Area> areas;
      PtrMap<Actor> actors;
      std::shared_ptr<Player> player;

      Engine(std::istream &in_s, std::ostream &out_s);

      virtual ~Engine();

      std::deque<std::string> read_command();
      bool tick();
      void loop();

      void quit();

      void add_actor(std::shared_ptr<Actor> who, const std::string &where);

      void connect_areas(const std::string &area_a, const std::string &dir_a,
          const std::string &dir_b, const std::string &area_b);

      void talk(std::shared_ptr<Actor> who, const std::string &what) const;

      void import_entity(const std::unordered_map<std::string, std::string> &data);
  };
}

#endif
