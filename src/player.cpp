#include "player.hpp"

#include "actor.hpp"
#include "util/tokenizer.hpp"

#include <list>
#include <string>
#include <iostream>

namespace hoboquest {

  Player::Player(std::istream &in, std::ostream &out) :
    Actor::Actor("player", "Player"), _in(in), _out(out) {}

  CommandOutcome Player::execute(const std::string &command, std::list<std::string> &args) {
    return commands.execute(command, args, *this);
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

      CommandOutcome outcome = execute(command, tokens);

      switch (outcome) {
        case SUCCESS:
          return true;
        case NOT_FOUND:
          _out << "Unknown command '" << command << "', try again.\n";
          break;
        case ERROR:
          // noop
          break;
      }
      tokens.clear();
    }
    return false;
  }


  void Player::enter_area(std::shared_ptr<Area> area) {
    _out << "Entering " << *area << std::endl;
    area->describe(_out);
  }

  void Player::exit_area(std::shared_ptr<Area> area) {
  }


} /* hoboquest */ 
