#include "player.hpp"

#include "actor.hpp"
#include "../util/tokenizer.hpp"

#include <deque>
#include <string>
#include <iostream>

namespace hoboquest {

  Player::Player(std::istream &in, std::ostream &out) :
    Actor::Actor("player", "Hobo"), _in(in), _out(out), _turns_stationary(0) {
      _hp = _hp_max = 20;
      _damage = 5;

      observe("entered", [this](std::shared_ptr<Entity> e) {
        this->_turns_stationary = 0;
        return true;
      });
    }

  CommandOutcome Player::execute(const std::string &command, std::deque<std::string> &args) {
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
  bool Player::execute() {
    Player::token_container tokens;


    if (_turns_stationary++ < 1) {
      _out << std::endl << "Location: ";
      _location->describe(_out);
    }

    while (1) {
      _out << std::endl;
      tokens = command_prompt();
      _out << std::endl;

      std::string command = tokens.front();
      tokens.pop_front();

      CommandOutcome outcome = execute(command, tokens);

      switch (outcome) {
        case SUCCESS:
          return true;
        case NOT_FOUND:
          _out << "Unknown command '" << command << "', try again.\n";
          break;
        case NOOP:
        case ERROR:
          // noop
          break;
        case EXIT:
          message("Quitting...");
          return false;
      }
      tokens.clear();
    }
    return false;
  }

  unsigned Player::remove_money(unsigned amount) {
    unsigned removed = ContainerEntity::remove_money(amount);
    _out << "You lost $" << amount << "." << std::endl;
    return removed;
  }
  void Player::add_money(unsigned amount) {
    ContainerEntity::add_money(amount);
    _out << "You received $" << amount << "." << std::endl;
  }

  void Player::listen(std::shared_ptr<Entity> source, const std::string &said) {
    auto actor = std::dynamic_pointer_cast<Actor>(source);
    if (actor)
      _out << actor->name() << " says: " << said << std::endl;
    else
      _out << "You hear " << said << " coming from " << source->name() << "." << std::endl;
  }

  bool Player::has_quest(const std::string &id) const {
    return quests.has(id);
  }
  bool Player::completed_quest(const std::string &id) const {
    auto quest = quests.get(id);
    return quest && quest->completed();
  }

} /* hoboquest */
