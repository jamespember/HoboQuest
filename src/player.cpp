#include "player.hpp"

#include "actor.hpp"
#include "util/tokenizer.hpp"

#include <list>
#include <string>
#include <iostream>

namespace hoboquest {

  Player::Player(std::istream &in, std::ostream &out) :
    Actor::Actor("Player"), _in(in), _out(out) {}

  bool Player::execute(const std::string &command, std::list<std::string> &args) {
    return commands.try_execute(command, args, *this);
  }

  void Player::message(std::string msg) {
    _out << msg << std::endl;
  }
  std::ostream & Player::out() { return _out; }
  // std::istream & Player::in() { return _in; }

  Player::token_container Player::command_prompt() {
    std::string input;
    Player::token_container tokens;

    do {
      _out << "> ";

      if (!std::getline(_in, input))
        return tokens;

      tokenize(input, tokens, "\n\t ");
    } while (tokens.size() < 1);

    return tokens;
  }

  // Prompts the player input for a command and then attempts to execute it.
  // This is repeated until a valid command read and successfully executed.
  bool Player::interact() {
    Player::token_container tokens;

    while (1) {
      tokens = command_prompt();

      // Quit?
      if (tokens.size() < 1 || tokens.front() == "quit")
        return message("Quitting..."), false;

      std::string command = tokens.front();
      tokens.pop_front();

      if (execute(command, tokens))
        return true;

      // message("Invalid command, try again.");
      tokens.clear();
    }
    return false;
  }


} /* hoboquest */ 
