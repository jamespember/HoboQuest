#ifndef HOBO_SIMPLE_COMMAND
#define HOBO_SIMPLE_COMMAND

#include "command.hpp"

#include <deque>
#include <string>
#include <functional>

namespace hoboquest {
  class Player;

  // FIXME: Change return type to CommandOutcome
  typedef std::function<bool(Player&, std::deque<std::string>&)> command_function;

  class SimpleCommand : public Command {
    protected:
      command_function _executor;

    public:
      SimpleCommand(const std::string &name, const std::string &alias, const command_function &executor);
      SimpleCommand(const std::string &name, const command_function &executor);

      ~SimpleCommand();

      CommandOutcome execute(Player &player, std::deque<std::string> &args);

  };
} /* hoboquest */ 

#endif
