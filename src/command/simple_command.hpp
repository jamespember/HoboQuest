#ifndef HOBO_SIMPLE_COMMAND
#define HOBO_SIMPLE_COMMAND

#include "command.hpp"

#include <list>
#include <string>
#include <functional>

namespace hoboquest {
  class Player;

  typedef std::function<bool(Player&, std::list<std::string>&)> command_function;

  class SimpleCommand : public Command {
    protected:
      command_function _executor;

    public:
      SimpleCommand(const std::string &name, const std::string &alias, const command_function &executor);
      SimpleCommand(const std::string &name, const command_function &executor);

      ~SimpleCommand();

      CommandOutcome execute(Player &player, std::list<std::string> &args);

  };
} /* hoboquest */ 

#endif
