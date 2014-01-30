#include "go.hpp"

#include <deque>
#include <string>
#include "../actor/player.hpp"

namespace hoboquest {

  GoCommand::GoCommand(const std::string &direction, const std::string &alias) :
    Command(direction, alias) {}
  GoCommand::GoCommand(const std::string &direction) :
    Command(direction) {}
  GoCommand::GoCommand() : Command("go", "g") {}

  CommandOutcome GoCommand::execute(Player &player, std::deque<std::string> &args) {
    auto location = player.location();

    if (location == nullptr) {
      player.message("You can't go anywhere!");
      return ERROR;
    }

    if (args.empty()) {
      player.message("Go where?");
      location->describe_exits(player.out());
      return ERROR;
    }

    auto area = location->get_exit(args.front());

    if (!area || !player.go(args.front())) {
      player.out() << "You can't go " << args.front() << std::endl;
      location->describe_exits(player.out());
      return ERROR;
    }

    return SUCCESS;
  }

} /* hoboquest */ 
