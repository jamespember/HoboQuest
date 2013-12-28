#ifndef HOBO_COMMANDABLE
#define HOBO_COMMANDABLE

#include "command.hpp"

#include <memory>
#include <list>
#include <string>

namespace hoboquest {
  class Player;

  class Commandable {
    typedef std::list<std::shared_ptr<Command>> container_type;

    protected:
      std::list<std::shared_ptr<Command>> _commands;

      container_type::const_iterator get_command_iterator(const std::string &name) const;

    public:

      Commandable();
      ~Commandable();

      bool add_command(std::shared_ptr<Command>);
      bool remove_command(const std::string &name);
      bool has_command(const std::string &name) const;

      bool try_execute(const std::string &name, Player &player,
          std::list<std::string> &args);
  };
} /* hoboquest */ 

#endif
