#include "commandable.hpp"

#include "command.hpp"
#include "player.hpp"

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

  Commandable::container_type::const_iterator
    Commandable::get_command_iterator(const std::string &name) const {
    Commandable::container_type::const_iterator it = _commands.begin(), itend = _commands.end();
    if (_commands.empty())
      return itend;
    for (; it != itend; it++)
      if ((*it)->responds_to(name))
        return it;
    return itend;
  }

  // Removes (last) command whose name or alias matches.
  bool Commandable::remove_command(const std::string &name) {
    auto it = get_command_iterator(name);
    if (it == _commands.end())
      return false;
    _commands.erase(it);
    return true;
  }

  bool Commandable::has_command(const std::string &name) const {
    return get_command_iterator(name) != _commands.end();
  }

  bool Commandable::try_execute(const std::string &name, Player &player,
      std::list<std::string> &args) {
    Commandable::container_type::const_iterator it = get_command_iterator(name);
    if (it == _commands.end())
      return false;
    return (*it)->execute(player, args);
  }

} /* hoboquest */ 
