#include "actor.hpp"
#include "container_entity.hpp"
#include "item/item.hpp"

#include <vector>
#include <unordered_map>

namespace hoboquest {

  Actor::Actor(const std::string &id, const std::string &name) :
  ContainerEntity(ACTOR, id, name), _active(false), _hp_max(1) {
    _hp = _hp_max;
  }

  Actor::~Actor() {}

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

  void Actor::enter_area(std::shared_ptr<Area> area) {
  }

  void Actor::exit_area(std::shared_ptr<Area> area) {
  }

  void Actor::move_to(std::shared_ptr<Area> area) {
    if (_location != nullptr) {
      exit_area(_location);
      area->remove_actor(_id);
    }
    area->add_actor(shared_from_this());
    _location = area;
    enter_area(_location);
  }

  void Actor::tick() {}
      
} /* hoboquest  */ 

