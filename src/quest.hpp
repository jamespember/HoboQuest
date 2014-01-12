#ifndef HOBO_QUEST
#define HOBO_QUEST

#include "entity.hpp"

#include <memory>
#include <string>

namespace hoboquest {
  class Quest : public Entity {
    protected:
      int _state;
      bool _finished;

    public:
      Quest(const std::string &id, const std::string &name) :
        Entity(QUEST, id, name), _state(0), _finished(false) {}

      virtual ~Quest();

      int state() const { return _state; }
      bool finished() const { return _finished; }

      virtual void describe(std::ostream &out) const {
        Entity::describe(out);
      }

  };
} /* hoboquest  */

#endif
