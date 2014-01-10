#include "go.hpp"

#include <vector>
#include <string>
#include "../player.hpp"

namespace hoboquest {

  GoCommand::GoCommand(const std::string &direction, const std::string &alias) :
    Command(direction, alias) {}
  GoCommand::GoCommand(const std::string &direction) :
    Command(direction) {}
  GoCommand::GoCommand() : Command("go", "g") {}

  GoCommand::~GoCommand() {}

  bool GoCommand::execute(Player &player, std::list<std::string> &args) {
    auto location = player.location();

    if (location == nullptr) {
      player.message("You can't go anywhere!");
      return false;
    }

    if (args.empty()) {
      player.message("Go where?");
      location->describe_exits(player.out());
      return false;
    }

    if (!location->has_exit(args.front())) {
      player.out() << "You can't go " << args.front() << ".\n";
      location->describe_exits(player.out());
      return false;
    }

    player.move_to(location->get_exit(args.front()));
    return true;
  }

} /* hoboquest */ 
