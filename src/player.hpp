#ifndef HOBO_PLAYER
#define HOBO_PLAYER

#include "actor.hpp"
#include "quest.hpp"
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
      PtrMap<Quest> quests;

      Player(std::istream &in, std::ostream &out);

      CommandOutcome execute(const std::string &command, std::list<std::string> &args);

      void message(std::string msg);
      std::ostream & out();
      // std::istream & in();

      token_container command_prompt();
      bool interact();

      // void enter_area(std::shared_ptr<Area> area);
      // void exit_area(std::shared_ptr<Area> area);

      bool has_quest(const std::string &id) const;
      bool completed_quest(const std::string &id) const;

  };
} /* hoboquest */ 

#endif
