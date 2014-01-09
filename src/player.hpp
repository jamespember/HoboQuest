#ifndef HOBO_PLAYER
#define HOBO_PLAYER

#include "actor.hpp"
#include "command/commandable.hpp"

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

      CommandOutcome execute(const std::string &command, std::list<std::string> &args);

      void message(std::string msg);
      std::ostream & out();
      // std::istream & in();

      token_container command_prompt();
      bool interact();

  };
} /* hoboquest */ 

#endif
