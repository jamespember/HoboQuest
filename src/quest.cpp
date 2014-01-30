#include "quest.hpp"
#include "engine.hpp"
#include "entity.hpp"
#include "actor/player.hpp"

#include <memory>
#include <string>
#include <iostream>

namespace hoboquest {
  Quest::Quest(const std::string &id, const std::string &name, Engine &engine) :
    Entity(QUEST, id, name), _engine(engine), _state(INACTIVE) {}

  Quest::~Quest() {}

  QuestState Quest::state() const { return _state; }
  bool Quest::started() const { return _state != INACTIVE; }
  bool Quest::completed() const { return _state == COMPLETED; }

  bool Quest::start() {
    if (_state != INACTIVE)
      return false;
    auto ptr = std::static_pointer_cast<Quest>(shared_from_this());
    if (!_engine.player->quests.add(ptr))
      return false;
    _state = STARTED;
    _engine.player->notify("quest_started", shared_from_this());
    on_start();
    return true;
  }

  bool Quest::complete() {
    if (_state == COMPLETED)
      return false;
    _state = COMPLETED;
    _engine.player->notify("quest_completed", shared_from_this());
    on_complete();
    return true;
  }

  // Advance quest to next stage, specified by the description
  void Quest::progress(const std::string &description) {
    _stages.push_back(description);
    if (_state == INACTIVE)
      return;
    _state = PROGRESSED;
    _engine.player->notify("quest_progressed", shared_from_this());
    notify("progressed", shared_from_this());
  }

  void Quest::on_start() {
    notify("started", shared_from_this());
  }
  void Quest::on_complete() {
    notify("completed", shared_from_this());
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
    std::string status;
    switch (_state) {
      case INACTIVE:
        status = "Not yet started";
        break;
      case COMPLETED:
        status = "Completed";
        break;
      case STARTED:
      case PROGRESSED:
        out << std::endl << "  " << _stages.back() << std::endl;
        return;
    }
    out << " - " << status << std::endl;
  }
} /* hoboquest  */
