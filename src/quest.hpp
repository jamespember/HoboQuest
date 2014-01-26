#ifndef HOBO_QUEST
#define HOBO_QUEST

#include "entity.hpp"

#include <memory>
#include <string>

namespace hoboquest {
  class Player;

  class Quest : public Entity {
    protected:
      bool _completed;
      std::list<std::string> _stages;
      std::shared_ptr<Player> _player;

    public:
      Quest(const std::string &id, const std::string &name);

      virtual ~Quest();

      void assign_to(std::shared_ptr<Player> player);

      unsigned state() const;
      bool completed() const;

      bool complete();

      // Advance quest to next stage, specified by the description
      void advance(const std::string &description);

      virtual void describe_stages(std::ostream &out) const;
      virtual void describe(std::ostream &out) const;

  };
} /* hoboquest  */

#endif
