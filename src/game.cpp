#include "game.hpp"

#include <iostream>
#include <string>
#include <vector>

#define DEBUGGING 1
#include "util/debug.hpp"
#include "util/tokenizer.hpp"

#include "area.hpp"
#include "item.hpp"
#include "actor.hpp"
// #include "player.hpp"

namespace hoboquest {
  Game::Game(std::istream &in_s, std::ostream &out_s) : in(in_s), out(out_s) {
    out << "HoboQuest starting...\n";
    this->loop();
  }

  // Reads input from input stream until a valid command is given, then return it.
  std::vector<std::string> Game::read_command() {
    std::string input;
    std::vector<std::string> tokens;

    do {
      out << "> ";

      // Read and tokenize input line
      std::getline(in, input);
      tokenize(input, tokens, "\n\t ");

      #if DEBUGGING
      DEBUG("Input tokens:");
      for (std::string t : tokens)
        DEBUG(": " << t);
      DEBUG("");
      #endif

    } while (tokens.size() < 1);
    return tokens;
  }

  void Game::tick() {
  }

  void Game::loop() {
    while (1) {
      auto tokens = this->read_command();

      if (tokens[0] == "quit") {
        DEBUG("quitting...");
        return;
      }

      this->tick();
    }
  }
} /* hoboquest */ 
