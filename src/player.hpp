#ifndef HOBO_PLAYER
#define HOBO_PLAYER

#include "actor.hpp"

#include <string>

namespace hoboquest {
  class Player : public Actor {
    protected:

    public:
      Player();
      virtual ~Player();
  };
} /* hoboquest */ 

#endif
