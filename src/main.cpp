#include "game/game.hpp"

#ifdef TESTS
#include "test/run_tests.hpp"
#endif

#include <iostream>
#include <string>
#include <cstring>

int main(int argc, char *argv[]) {
  // Built with tests?
  #ifdef TESTS
  if (argc > 1 && strcmp(argv[1], "test") == 0)
    return run_tests();
  #endif

	hoboquest::Game g(std::cin, std::cout);
  g.loop();

  return 0;
}


