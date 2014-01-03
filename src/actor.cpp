#include "actor.hpp"

#include <vector>
#include <unordered_map>
#include "container.hpp"
#include "item/item.hpp"

namespace hoboquest {

  Actor::Actor(const std::string &name) : 
	_name(name), _active(false), _hp_max(1) {
    _hp = _hp_max;
  }

  Actor::~Actor() {}
  
  std::string Actor::name() const { return _name; }
  void Actor::set_name(const std::string &name) { _name = name; }

  bool Actor::active() const          { return _active; }
  int  Actor::damage() const          { return _damage; }
  int  Actor::hp() const              { return _hp; }
  int  Actor::hp_max() const          { return _hp_max; }
  void Actor::set_active(bool active) { _active = active; }
  void Actor::set_damage(int damage)  { _damage = damage; }
  void Actor::set_hp(int hp)          { _hp = hp; }
  void Actor::set_hp_max(int hp_max)  { _hp_max = hp_max; }

  const std::shared_ptr<Area> Actor::location() const { return _location; }
  std::shared_ptr<Area> Actor::location() { return _location; }

  void Actor::on_enter(std::shared_ptr<Area> area) {
  }

  void Actor::on_exit(std::shared_ptr<Area> area) {
  }

  void Actor::move_to(std::shared_ptr<Area> area) {
    if (_location != nullptr)
      on_exit(_location);
    _location = area;
    on_enter(_location);
    // TODO: Trigger on exit/enter for areas as well?
  }

  void Actor::tick() {}
      
} /* hoboquest  */ 

