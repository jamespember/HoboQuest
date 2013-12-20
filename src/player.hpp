#ifndef HOBO_PLAYER
#define HOBO_PLAYER

#include "actor.hpp"

#include <string>
#include <iostream>
#include <vector>

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

      std::vector<std::string> read_command();
      bool interact();

  };
} /* hoboquest */ 

#endif
