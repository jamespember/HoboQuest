#ifndef HOBO_ACTOR
#define HOBO_ACTOR

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include "container.hpp"
#include "area.hpp"
#include "item.hpp"

namespace hoboquest {
  class Actor : public Container {
    protected:
      string _name;
      bool _active;
      std::unordered_map<string, int> _stats;
      std::shared_ptr<Area> _location;

    public:
      Actor(string name) : _name(name) : _active(false) {
        _stats["hp"] = 1;
        _stats["damage"] = 1;
        _stats["capacity"] = 0;
      }

      void on_enter(std::shared_ptr<Area> area) {
      }

      void on_exit(std::shared_ptr<Area> area) {
      }

      void move_to(std::shared_ptr<Area> area) {
        if (*area)
          on_exit(_location);
        _location = area;
        on_enter(_location);
      }

      void tick() {}
      
  };
} /* hoboquest  */ 

#endif
