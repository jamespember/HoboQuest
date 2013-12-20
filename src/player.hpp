#ifndef HOBO_PLAYER
#define HOBO_PLAYER

#include "actor.hpp"

#include <string>
#include <iostream>

namespace hoboquest {
  class Player : public Actor {

    protected:
      std::istream &_in;
      std::ostream &_out;

    public:
      Player(std::istream &in, std::ostream &out);
      virtual ~Player();

      void message(std::string msg);
      std::ostream & out();
      std::istream & in();

  };
} /* hoboquest */ 

#endif
