#ifndef HOBO_COMMAND
#define HOBO_COMMAND

#include <list>
#include <string>
#include <ostream>

namespace hoboquest {
  class Player;

  enum CommandOutcome { SUCCESS, NOOP, ERROR, EXIT, NOT_FOUND };

  class Command {

    public:
      const std::string name;
      const std::string alias;

      Command(const std::string &name, const std::string &alias);
      Command(const std::string &name);

      virtual ~Command();

      bool has_alias() const;
      // const std::string & name() const;
      // const std::string & alias() const;
      // void set_name(const std::string &name);
      // void set_alias(const std::string &alias);

      bool responds_to(const std::string &cmd) const;

      virtual CommandOutcome execute(Player &player, std::list<std::string> &args) = 0;

  };

  inline std::ostream & operator << (std::ostream &out, const Command &c) {
    out << c.name;
    if (!c.alias.empty())
      out << " (" << c.alias << ")";
    return out;
  }
} /* hoboquest */ 

#endif
