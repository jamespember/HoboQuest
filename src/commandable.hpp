#ifndef HOBO_COMMANDABLE
#define HOBO_COMMANDABLE

#include <memory>
#include <unordered_map>
#include <string>

#include "command.hpp"
#include "player.hpp"

namespace hoboquest {
  class Commandable {
    protected:
      std::unordered_map<std::string, std::shared_ptr<Command>> _commands;

    public:
      Commandable();
      virtual ~Commandable();

      virtual bool add_command(std::shared_ptr<Command>);
      virtual bool remove_command(const std::string &name);
      virtual bool has_command(const std::string &name) const;

      virtual bool try_execute(const std::string &name, Player &player,
          std::vector<std::string> &args);
  };
} /* hoboquest */ 

#endif
