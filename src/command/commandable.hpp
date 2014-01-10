#ifndef HOBO_COMMANDABLE
#define HOBO_COMMANDABLE

#include "command.hpp"

#include <memory>
#include <list>
#include <string>

namespace hoboquest {
  class Player;

  enum CommandOutcome { SUCCESS, ERROR, NOT_FOUND };

  class Commandable {
    typedef std::list<std::shared_ptr<Command>> container_type;

    protected:
      container_type _commands;

      container_type::iterator get_iterator(const std::string &name);
      container_type::const_iterator get_iterator(const std::string &name) const;

    public:

      Commandable();
      ~Commandable();

      const container_type & get_commands() const;

      bool add_command(std::shared_ptr<Command>);
      bool remove_command(const std::string &name);
      bool has_command(const std::string &name) const;

      CommandOutcome execute(const std::string &name,
          std::list<std::string> &args, Player &player);

      friend std::ostream & operator << (std::ostream &out, const Commandable &c);
  };

  inline std::ostream & operator << (std::ostream &out, const Commandable &c) {
    if (c._commands.empty()) {
      out << "  (No commands available)." << std::endl;
      return out;
    }
    for (const auto &cmd : c._commands)
      out << "  " << (*cmd) << std::endl;
    return out;
  }
} /* hoboquest */ 

#endif
