#ifndef HOBO_WALKER
#define HOBO_WALKER

#include "actor.hpp"

#include <string>
#include <cstdlib>
#include <ctime>

namespace hoboquest {
  class Walker : public Actor {
    protected:
      unsigned randomChoice(unsigned min, unsigned max) const;

    public:
      Walker(const std::string &id, const std::string &name);
      virtual ~Walker();

      virtual void tick();

      virtual void on_interact(std::shared_ptr<Actor> actor);
  };
} /* hoboquest */ 

#endif
