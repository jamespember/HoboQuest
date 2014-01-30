#ifndef HOBO_COMMANDABLE
#define HOBO_COMMANDABLE

#include "command.hpp"

#include <memory>
#include <deque>
#include <list>
#include <string>

namespace hoboquest {
  class Player;

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
          std::deque<std::string> &args, Player &player);

      friend std::ostream & operator << (std::ostream &out, const Commandable &c);
  };

  inline std::ostream & operator << (std::ostream &out, const Commandable &c) {
    if (c._commands.empty()) {
      out << "  (No commands available)." << std::endl;
      return out;
    }
    // Output available commands in reverse order (first added listed first)
    for (auto it = c._commands.rbegin(), rend = c._commands.rend(); it != rend; it++)
      out << "  " << (**it) << std::endl;
    return out;
  }
} /* hoboquest */ 

#endif
