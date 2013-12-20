#include "player.hpp"
#include "actor.hpp"

#include <string>
#include <iostream>

namespace hoboquest {

  Player::Player(std::istream &in, std::ostream &out) :
    Actor::Actor("Player"), _in(in), _out(out) {}

  Player::~Player() {}

  void Player::message(std::string msg) {
    this->_out << msg << std::endl;
  }
  std::ostream & Player::out() { return this->_out; }
  std::istream & Player::in() { return this->_in; }

} /* hoboquest */ 
