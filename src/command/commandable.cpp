#include "commandable.hpp"

#include "command.hpp"
#include "../player.hpp"

#include <memory>
#include <list>
#include <string>
#include <cassert>
#include <iostream>

namespace hoboquest {

  Commandable::Commandable() {}
  Commandable::~Commandable() {}

  bool Commandable::add_command(std::shared_ptr<Command> cmd) {
    if (has_command(cmd->name))
      return false;
    _commands.push_front(cmd);
    return true;
  }

  Commandable::container_type::iterator
    Commandable::get_iterator(const std::string &name) {
    auto end = _commands.end();
    for (auto it = _commands.begin(); it != end; it++)
      if ((*it)->responds_to(name))
        return it;
    return end;
  }

  Commandable::container_type::const_iterator
    Commandable::get_iterator(const std::string &name) const {
    auto end = _commands.end();
    for (auto it = _commands.begin(); it != end; it++)
      if ((*it)->responds_to(name))
        return it;
    return end;
  }

  // Removes (last) command whose name or alias matches.
  bool Commandable::remove_command(const std::string &name) {
    auto it = get_iterator(name);
    if (it == _commands.end())
      return false;
    _commands.erase(it);
    return true;
  }

  bool Commandable::has_command(const std::string &name) const {
    return get_iterator(name) != _commands.end();
  }

  bool Commandable::try_execute(const std::string &name,
      std::list<std::string> &args, Player &player) {
    auto it = get_iterator(name);
    if (it == _commands.end())
      return false;
    return (*it)->execute(player, args);
  }

} /* hoboquest */ 
