#ifndef HOBO_COMMAND
#define HOBO_COMMAND

#include <list>
#include <string>

namespace hoboquest {
  class Player;

  class Command {
    protected:
      std::string _name;
      std::string _alias;

    public:
      Command(const std::string &name, const std::string &alias);
      Command(const std::string &name);
      virtual ~Command();

      const std::string & name() const;
      const std::string & alias() const;
      void set_name(const std::string &name);
      void set_alias(const std::string &alias);
      bool has_alias() const;

      bool responds_to(const std::string &name) const;

      virtual bool execute(Player &player, std::list<std::string> &args) = 0;

  };
} /* hoboquest */ 

#endif
