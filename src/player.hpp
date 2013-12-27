#ifndef HOBO_PLAYER
#define HOBO_PLAYER

#include "game.hpp"
#include "actor.hpp"
#include "commandable.hpp"

#include <string>
#include <iostream>
#include <vector>

namespace hoboquest {
  class Player : public Actor {

    protected:
      std::istream &_in;
      std::ostream &_out;

    public:
      Commandable commands;
      Game &game;

      Player(Game &game, std::istream &in, std::ostream &out);

      void message(std::string msg);
      // std::ostream & out();
      // std::istream & in();

      std::list<std::string> read_command();
      bool interact();

  };
} /* hoboquest */ 

#endif
