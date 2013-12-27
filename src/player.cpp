#include "player.hpp"

#include "game.hpp"
#include "actor.hpp"
#include "util/tokenizer.hpp"

#include <list>
#include <string>
#include <iostream>

namespace hoboquest {

  Player::Player(Game &game, std::istream &in, std::ostream &out) :
    Actor::Actor("Player"), _in(in), _out(out), game(game) {}

  void Player::message(std::string msg) {
    _out << msg << std::endl;
  }
  // std::ostream & Player::out() { return _out; }
  // std::istream & Player::in() { return _in; }

  // Reads input from input stream until a valid command is given, then return it.
  std::list<std::string> Player::read_command() {
    std::string input;
    std::list<std::string> tokens;

    do {
      _out << "> ";

      // Read and tokenize input line
      if (!std::getline(_in, input))
        return tokens;
      tokenize(input, tokens, "\n\t ");
    } while (tokens.size() < 1);

    return tokens;
  }

  bool Player::interact() {
    auto tokens = read_command();

    if (tokens.size() < 1 || tokens.front() == "quit") {
      _out << "\nQuitting...\n";
      return false;
    }

    // TODO: Interpret command
    std::string command = tokens.front();
    tokens.pop_front();
    commands.try_execute(command, *this, tokens);

    return true;
  }


} /* hoboquest */ 
