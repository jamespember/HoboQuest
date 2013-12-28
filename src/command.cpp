#include "command.hpp"

#include <vector>
#include <string>
#include "player.hpp"

namespace hoboquest {

  Command::Command(const std::string &name, const std::string &alias) :
    name(name), alias(alias) {}
  Command::Command(const std::string &name) :
    name(name), alias("") {}

  Command::~Command() {}

  bool Command::has_alias() const { return !alias.empty(); }
  // const std::string & Command::name() const { return _name; }
  // const std::string & Command::alias() const { return _alias; }
  // void Command::set_name(const std::string &name) { _name = name; }
  // void Command::set_alias(const std::string &alias) { _alias = alias; }

  bool Command::responds_to(const std::string &cmd) const {
    return cmd == name || cmd == alias;
  }

} /* hoboquest */ 
