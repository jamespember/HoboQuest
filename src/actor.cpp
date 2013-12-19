#include "actor.hpp"

#include <vector>
#include <unordered_map>
#include "container.hpp"
#include "item.hpp"

namespace hoboquest {

  Actor::Actor(const std::string name) : _name(name), _active(false), _hp_max(1) {
    _hp = _hp_max;
  }
  
  std::string Actor::get_name() const {
		return this->_name;
  }
  
  void Actor::set_name(std::string name) {
		this->_name = name;
  }

  void Actor::on_enter(std::shared_ptr<Area> area) {
  }

  void Actor::on_exit(std::shared_ptr<Area> area) {
  }

  void Actor::move_to(std::shared_ptr<Area> area) {
    if (area != nullptr)
      on_exit(_location);
    _location = area;
    on_enter(_location);
  }

  void Actor::action() {}
      
} /* hoboquest  */ 

