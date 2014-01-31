#ifndef HOBO_RANGER
#define HOBO_RANGER

#include "walker.hpp"

#include <string>
#include <cstdlib>
#include <ctime>

namespace hoboquest {
  class Ranger : public Walker {
    protected:
      bool _spoken_with_player;
      bool _dropped_badge;

    public:
      std::shared_ptr<Equippable> badge;

      Ranger();

      virtual void init();
      virtual void tick();
  };
} /* hoboquest */ 

#endif
