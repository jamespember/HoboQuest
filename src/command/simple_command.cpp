#include "simple_command.hpp"

#include "command.hpp"
#include "../player.hpp"

#include <deque>
#include <string>

namespace hoboquest {

  SimpleCommand::SimpleCommand(const std::string &name, const std::string &alias, const command_function &executor) :
    Command(name, alias), _executor(executor) {}
  SimpleCommand::SimpleCommand(const std::string &name, const command_function &executor) :
    Command(name), _executor(executor) {}

  SimpleCommand::~SimpleCommand() {}

  // FIXME: Return actual outcome
  CommandOutcome SimpleCommand::execute(Player &player, std::deque<std::string> &args) {
    return _executor(player, args) ? SUCCESS : ERROR;
  }

} /* hoboquest */
