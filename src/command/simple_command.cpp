#include "simple_command.hpp"

#include "command.hpp"
#include "../player.hpp"

#include <vector>
#include <string>

namespace hoboquest {

  SimpleCommand::SimpleCommand(const std::string &name, const std::string &alias, const command_function &executor) :
    Command(name, alias), _executor(executor) {}
  SimpleCommand::SimpleCommand(const std::string &name, const command_function &executor) :
    Command(name), _executor(executor) {}

  SimpleCommand::~SimpleCommand() {}

  CommandOutcome SimpleCommand::execute(Player &player, std::list<std::string> &args) {
    return _executor(player, args) ? SUCCESS : ERROR;
  }

} /* hoboquest */
