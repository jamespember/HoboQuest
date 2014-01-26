#include "quest.hpp"
#include "entity.hpp"
#include "player.hpp"

#include <memory>
#include <string>
#include <iostream>

namespace hoboquest {
  Quest::Quest(const std::string &id, const std::string &name) :
    Entity(QUEST, id, name), _completed(false) {}

  Quest::~Quest() {}

  void Quest::assign_to(std::shared_ptr<Player> player) {
    _player = player;
    _player->notify("quest_started", shared_from_this());
  }

  unsigned Quest::state() const { return _completed ? 999 : _stages.size(); }
  bool Quest::completed() const { return _completed; }

  bool Quest::complete() {
    if (_completed)
      return false;
    _completed = true;
    notify("completed", shared_from_this());
    if (_player) _player->notify("quest_completed", shared_from_this());
    return true;
  }

  // Advance quest to next stage, specified by the description
  void Quest::advance(const std::string &description) {
    _stages.push_back(description);
    notify("advanced", shared_from_this());
    if (_player) _player->notify("quest_advanced", shared_from_this());
  }

  void Quest::describe_stages(std::ostream &out) const {
    unsigned num = 1, curr = state();
    std::string status;

    for (const auto &stage : _stages) {
      if (num < curr)
        status = "Completed";
      else if (num == curr)
        status = "Current";
      else if (num > curr)
        status = "Not yet started";
      out << "  [" << status << "] " << stage << std::endl;
      ++num;
    }
  }

  void Quest::describe(std::ostream &out) const {
    Entity::describe_short(out);
    std::string status = "Active";
    if (completed())
      status = "Completed";
    else if (state() == 0)
      status = "Not yet started";
    out << " - " << status << std::endl;
    describe_stages(out);
  }
} /* hoboquest  */
