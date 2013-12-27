#include "commandable.hpp"

#include <vector>
#include <string>

#include "command.hpp"
#include "player.hpp"

namespace hoboquest {

  Commandable::Commandable() {}
  Commandable::~Commandable() {}

  bool Commandable::add_command(std::shared_ptr<Command> cmd) {
    if (has_command(cmd->name()))
      return false;
    _commands[cmd->name()] = cmd;
    return true;
  }
  bool Commandable::remove_command(const std::string &name) {
    return _commands.erase(name) > 0;
  }
  bool Commandable::has_command(const std::string &name) const {
    return _commands.count(name) > 0;
  }

  bool Commandable::try_execute(const std::string &name, Player &player,
      std::vector<std::string> &args) {
    if (!has_command(name))
      return false;
    std::shared_ptr<Command> p_cmd = _commands[name];
    if (!p_cmd->can_execute(player))
      return false;
    return p_cmd->execute(player, args);
  }

} /* hoboquest */ 
