#include "actor.hpp"
#include "../area.hpp"
#include "../container_entity.hpp"
#include "../item/item.hpp"
#include "../item/equippable.hpp"

#include <memory>
#include <vector>
#include <unordered_map>

namespace hoboquest {

  Actor::Actor(const std::string &id, const std::string &name) :
  ContainerEntity(ACTOR, id, name), _alive(true), _hp_max(1) {
    _hp = _hp_max;
  }

  Actor::~Actor() {}

  bool Actor::alive() const  { return _alive; }
  int  Actor::hp() const     { return _hp; }
  int  Actor::hp_max() const { return _hp_max; }
  int  Actor::damage() const { return _damage; }

  void Actor::set_hp(int hp) {
    _hp = hp < 0 ? 0 : hp;
    notify("changed_hp", shared_from_this());
    if (_hp < 1)
      kill();
  }

  int Actor::modify_hp(int modifier) {
    _hp += modifier;
    if (_hp < 0) {
      modifier -= _hp;
      _hp = 0;
    } else if (_hp > _hp_max) {
      modifier -= (_hp - _hp_max);
      _hp = _hp_max;
    }
    notify("changed_hp", shared_from_this());
    if (_hp < 1)
      kill();
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

  const std::shared_ptr<Equippable> Actor::get_equipment(const std::string &what) const {
    return _equipped.get(what);
  }

  std::shared_ptr<Item> Actor::remove_item(const std::string &id) {
    unequip(id);
    return ContainerEntity::remove_item(id);
  }

  void Actor::move_to(std::shared_ptr<Area> area) {
    auto previous = _location;
    if (previous != nullptr) {
      previous->remove_actor(_id);
    }
    _location = area;
    notify("exited", previous);
    notify("entered", _location);
    area->add_actor(std::static_pointer_cast<Actor>(shared_from_this()));
  }

  bool Actor::go(const std::string &where) {
    auto loc = location();
    if (loc == nullptr)
      return false;
    auto area = loc->get_exit(where);
    if (!area)
      return false;
    move_to(area);
    return true;
  }

  bool Actor::consume(const std::string &what) {
    auto item = get_item(what);
    if (!item || !item->is_consumable())
      return false;

    remove_item(what);
    notify("consumed", std::static_pointer_cast<Entity>(item));
    item->on_consume(std::static_pointer_cast<Actor>(shared_from_this()));
    return true;
  }

  bool Actor::pickup(const std::string &what) {
    auto loc = location();
    if (!loc)
      return false;
    auto item = loc->get_item(what);
    if (item && add_item(item)) {
      loc->remove_item(what);
      notify("picked_up", std::static_pointer_cast<Entity>(item));
      return true;
    }
    return false;
  }

  bool Actor::drop(const std::string &what) {
    auto loc = location();
    if (!loc)
      return false;
    auto item = get_item(what);
    if (item && loc->add_item(item)) {
      remove_item(what);
      notify("dropped", std::static_pointer_cast<Entity>(item));
      return true;
    }
    return false;
  }

  bool Actor::give(std::shared_ptr<Actor> actor, const std::string &what) {
    auto item = get_item(what);
    if (item && actor->add_item(item)) {
      remove_item(what);
      notify("gave", std::static_pointer_cast<Entity>(item));
      return true;
    }
    return false;
  }

  bool Actor::steal(std::shared_ptr<Actor> actor, const std::string &what) {
    auto item = actor->get_item(what);
    if (item && add_item(item)) {
      actor->remove_item(what);
      notify("stole", std::static_pointer_cast<Entity>(item));
      return true;
    }
    return false;
  }

  bool Actor::equip(const std::string &what) {
    auto item = get_item(what);
    if (!item->is_equippable())
      return false;
    if (item && _equipped.add(std::static_pointer_cast<Equippable>(item))) {
      notify("equipped", std::static_pointer_cast<Entity>(item));
      return true;
    }
    return false;
  }

  bool Actor::unequip(const std::string &what) {
    auto item = _equipped.get(what);
    if (item) {
      _equipped.remove(what);
      notify("unequipped", std::static_pointer_cast<Entity>(item));
      return true;
    }
    return false;
  }

  void Actor::tick() {
    if (alive())
      notify("tick", shared_from_this());
  }

  bool Actor::kill() {
    if (!_alive)
      return false;
    _alive = false;
    _hp = 0;
    on_death();
    return true;
  }

  void Actor::interact(std::shared_ptr<Actor> actor) {
    notify("interact", actor);
  }

  void Actor::on_death() {
    notify("died", shared_from_this());
    set_name(name() + " (dead)");
  }

  void Actor::describe(std::ostream &out) const {
    ContainerEntity::describe(out);
  }

} /* hoboquest  */

