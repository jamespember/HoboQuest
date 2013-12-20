#include "command.hpp"

#include <vector>
#include <string>
#include "player.hpp"

namespace hoboquest {
  Command::Command(const std::string &name, const std::string &alias) :
    _name(name), _alias(alias) {}
  Command::Command(const std::string &name) :
    _name(name) {}

  Command::~Command() {}

  const std::string & Command::name() const { return this->_name; }
  const std::string & Command::alias() const { return this->_alias; }
  void Command::set_name(const std::string &name) { this->_name = name; }
  void Command::set_alias(const std::string &alias) { this->_alias = alias; }
  bool Command::has_alias() const { return !_alias.empty(); }

  bool Command::can_execute(Player &player) { return true; }

} /* hoboquest */ 
