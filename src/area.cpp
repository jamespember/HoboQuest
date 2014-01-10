#include "area.hpp"
#include "container_entity.hpp"

#include <iostream>

namespace hoboquest {

  Area::Area(const std::string &id, const std::string &name) :
    ContainerEntity(Entity::AREA, id, name) {}

  std::string Area::description() const { return _description; }

  void Area::set_description(const std::string description) { 
    _description = description;
  }

  void Area::add_exit(const std::string &direction, std::shared_ptr<Area> exit)  {
    _exits[direction] = exit;
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
    if (exit != nullptr)
      _exits.erase(direction);
    return exit;
  }

  bool Area::add_actor(std::shared_ptr<Actor> actor) {
    return _actors.add(actor);
  }

  bool Area::has_actor(const std::string &id) const {
    return _actors.has(id);
  }

  std::shared_ptr<Actor> Area::get_actor(const std::string &id) const {
    return _actors.get(id);
  }

  void Area::remove_actor(const std::string &id) {
    _actors.remove(id);
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

  void Area::describe(std::ostream &out) const {
    if (!_description.empty())
      out << _description << std::endl;
    describe_exits(out);
  }

  void Area::to_ostream(std::ostream &out) const {
    Entity::to_ostream(out);
  }
}
