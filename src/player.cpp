#include "player.hpp"

#include "game.hpp"
#include "actor.hpp"
#include "util/tokenizer.hpp"

#include <string>
#include <iostream>
#include <vector>

namespace hoboquest {

  Player::Player(Game &game, std::istream &in, std::ostream &out) :
    Actor::Actor("Player"), _in(in), _out(out), game(game) {}

  void Player::message(std::string msg) {
    this->_out << msg << std::endl;
  }
  // std::ostream & Player::out() { return this->_out; }
  // std::istream & Player::in() { return this->_in; }

  // Reads input from input stream until a valid command is given, then return it.
  std::vector<std::string> Player::read_command() {
    std::string input;
    std::vector<std::string> tokens;

    do {
      this->_out << "> ";

      // Read and tokenize input line
      if (!std::getline(this->_in, input))
        return tokens;
      tokenize(input, tokens, "\n\t ");
    } while (tokens.size() < 1);

    return tokens;
  }

  bool Player::interact() {
    auto tokens = this->read_command();

    if (tokens.size() < 1 || tokens[0] == "quit") {
      this->_out << "\nQuitting...\n";
      return false;
    }

    // TODO: Interpret command

    return true;
  }


} /* hoboquest */ 
