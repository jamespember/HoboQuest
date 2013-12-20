#ifndef HOBO_COMMAND
#define HOBO_COMMAND

#include <vector>
#include <string>
#include "player.hpp"

namespace hoboquest {
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

      virtual bool execute(Player &player, std::vector<std::string> &args) = 0;
      virtual bool can_execute(Player &player);
  };
} /* hoboquest */ 

#endif
