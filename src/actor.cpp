#include "actor.hpp"
#include "area.hpp"
#include "container_entity.hpp"
#include "item/item.hpp"

#include <memory>
#include <vector>
#include <unordered_map>

namespace hoboquest {

  Actor::Actor(const std::string &id, const std::string &name) :
  ContainerEntity(ACTOR, id, name), _hp_max(1) {
    _hp = _hp_max;
  }

  Actor::~Actor() {}

  bool Actor::alive() const  { return _hp > 0; }
  int  Actor::hp() const     { return _hp; }
  int  Actor::hp_max() const { return _hp_max; }
  int  Actor::damage() const { return _damage; }

  void Actor::set_hp(int hp) {
    _hp = hp < 0 ? 0 : hp;
    notify("changed_hp", shared_from_this());
    if (_hp < 1)
      notify("death", shared_from_this());
  }

  int Actor::modify_hp(int modifier) {
    _hp += modifier;
    if (_hp < 0) {
      modifier -= _hp;
      _hp = 0;
    } else if (_hp > _hp_max) {
      modifier -= _hp;
      _hp = _hp_max;
    }
    notify("changed_hp", shared_from_this());
    if (_hp < 1)
      notify("death", shared_from_this());
    return modifier;
  }

  void Actor::set_hp_max(int hp_max) {
    _hp_max = hp_max;
    notify("changed_hp_max", shared_from_this());
    if (_hp > _hp_max)
      set_hp(_hp_max);
  }

  void Actor::set_damage(int damage) {
    _damage = damage;
    notify("changed_damage", shared_from_this());
  }

  const std::shared_ptr<Area> Actor::location() const { return _location; }
  std::shared_ptr<Area> Actor::location() { return _location; }

  void Actor::move_to(std::shared_ptr<Area> area) {
    if (_location != nullptr) {
      notify("exit_area", _location);
      area->remove_actor(_id);
    }
    area->add_actor(std::static_pointer_cast<Actor>(shared_from_this()));
    _location = area;
    notify("enter_area", _location);
  }

  void Actor::tick() {}

  void Actor::describe(std::ostream &out) const {
    ContainerEntity::describe(out);
  }

} /* hoboquest  */

