#ifndef HOBO_PLAYER
#define HOBO_PLAYER

#include "actor.hpp"
#include "../quest.hpp"
#include "../command/commandable.hpp"

#include <string>
#include <iostream>
#include <deque>

namespace hoboquest {
  class Player : public Actor {
    typedef std::deque<std::string> token_container;

    protected:
      std::istream &_in;
      std::ostream &_out;
      unsigned _turns_stationary;

    public:
      Commandable commands;
      PtrMap<Quest> quests;

      Player(std::istream &in, std::ostream &out);

      CommandOutcome execute(const std::string &command, std::deque<std::string> &args);

      void message(std::string msg);
      std::ostream & out();
      // std::istream & in();

      token_container command_prompt();
      bool interact();

      unsigned remove_money(unsigned amount);
      void add_money(unsigned amount);

      bool has_quest(const std::string &id) const;
      bool completed_quest(const std::string &id) const;

  };
} /* hoboquest */ 

#endif
