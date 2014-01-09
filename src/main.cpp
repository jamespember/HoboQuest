#include "game/game.hpp"
// #include "parser.hpp"

#ifdef TESTS
#include "test/run_tests.hpp"
#endif

#include <string>
#include <cstring>
#include <fstream>

#define DEFINITIONS_FILE "game.txt"

int main(int argc, char *argv[]) {
  // Built with tests?
  #ifdef TESTS
  if (argc > 1 && strcmp(argv[1], "test") == 0)
    return run_tests();
  #endif

	hoboquest::Game g(std::cin, std::cout);
  // hoboquest::Parser parser(g);

  // // Open game definitions file
  // std::ifstream file(DEFINITIONS_FILE);

  // if (!file.is_open()) {
    // std::cout << "Game definitions file (" << DEFINITIONS_FILE << ") could not be read.\n";
    // return 1;
  // }

  // parser.parse(file);

  if (argc > 1 && strcmp(argv[1], "parse") == 0)
    return 0;

  g.loop();

  return 0;
}


