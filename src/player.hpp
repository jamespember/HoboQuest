#ifndef HOBO_PLAYER
#define HOBO_PLAYER

#include "actor.hpp"
#include "commandable.hpp"

#include <string>
#include <iostream>
#include <vector>

namespace hoboquest {
  class Player : public Actor {
    typedef std::list<std::string> token_container;

    protected:
      std::istream &_in;
      std::ostream &_out;

    public:
      Commandable commands;

      Player(std::istream &in, std::ostream &out);

      void message(std::string msg);
      // std::ostream & out();
      // std::istream & in();

      token_container command_prompt();
      bool interact();

  };
} /* hoboquest */ 

#endif
