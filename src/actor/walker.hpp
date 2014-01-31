#ifndef HOBO_WALKER
#define HOBO_WALKER

#include "actor.hpp"

#include <string>
#include <cstdlib>
#include <ctime>

namespace hoboquest {
  class Walker : public Actor {
    protected:
      bool _spoken_with_player;
      unsigned _turns_stationary;

      unsigned random_choice(unsigned min, unsigned max) const;
      void random_move();

    public:
      Walker(const std::string &id, const std::string &name);
      virtual ~Walker();

      virtual void tick();
  };
} /* hoboquest */ 

#endif
