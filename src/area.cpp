#include "area.hpp"
#include "container_entity.hpp"

#include <iostream>

namespace hoboquest {

  Area::Area(const std::string &id, const std::string &name) :
    ContainerEntity(Entity::AREA, id, name) {}

  void Area::add_exit(const std::string &direction, std::shared_ptr<Area> exit)  {
    _exits[direction] = exit;
    notify("add_exit", exit);
  }

  bool Area::has_exit(const std::string &direction) const {
    return _exits.count(direction) > 0;
  }

  std::shared_ptr<Area> Area::get_exit(const std::string &direction) const {
    if (!has_exit(direction))
      return nullptr;
    return _exits.at(direction);
  }

  std::shared_ptr<Area> Area::remove_exit(const std::string &direction) {
    auto exit = get_exit(direction);
    if (exit != nullptr) {
      _exits.erase(direction);
      notify("remove_exit", exit);
    }
    return exit;
  }

  bool Area::add_actor(std::shared_ptr<Actor> actor) {
    bool result = _actors.add(actor);
    if (result) notify("add_actor", actor);
    return result;
  }

  bool Area::has_actor(const std::string &id) const {
    return _actors.has(id);
  }

  std::shared_ptr<Actor> Area::get_actor(const std::string &id) const {
    return _actors.get(id);
  }

  void Area::remove_actor(const std::string &id) {
    auto removed = _actors.remove(id);
    if (removed)
      notify("remove_actor", removed);
  }

  void Area::describe_exits(std::ostream &out) const {
    if (_exits.empty()) {
      out << "There are no exits." << std::endl;
      return;
    }
    out << "Exits:" << std::endl;
    for (const auto &kv : _exits)
      out << "  " << kv.first << ": " << kv.second->name() << std::endl;
  }

  void Area::describe_actors(std::ostream &out) const {
    auto map = _actors.get_map();
    // Don't output anything if the are no actors, or if the player is the only one
    if (map.empty() || (map.size() == 1 && map.count("player") > 0))
      return;
    out << "Actors:" << std::endl;
    for (const auto &kv : map)
      if (kv.first != "player")
        out << "  " << kv.first << ": " << kv.second->name() << std::endl;
  }

  void Area::describe(std::ostream &out) const {
    Entity::describe(out);
    if (!_description.empty())
      out << _description << std::endl;
    describe_exits(out);
    describe_actors(out);
    describe_contents(out);
  }
}
