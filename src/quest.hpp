#ifndef HOBO_QUEST
#define HOBO_QUEST

#include "entity.hpp"

#include <memory>
#include <string>

namespace hoboquest {
  class Engine;
  class Player;

  enum QuestState { INACTIVE, STARTED, PROGRESSED, COMPLETED };

  class Quest : public Entity {
    protected:
      Engine &_engine;
      QuestState _state;
      std::list<std::string> _stages;

    public:
      Quest(const std::string &id, const std::string &name, Engine &engine);

      virtual ~Quest();

      QuestState state() const;
      bool started() const;
      bool completed() const;

      bool start();
      bool complete();

      // Advance quest to next stage, specified by the description
      void progress(const std::string &description);

      virtual void on_start();
      virtual void on_complete();

      virtual void describe_stages(std::ostream &out) const;
      virtual void describe(std::ostream &out) const;

  };
} /* hoboquest  */

#endif
