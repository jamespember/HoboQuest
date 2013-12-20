#include <iostream>
#include <string>
#include "game.hpp"
#include "actor.hpp"
#include "area.hpp"

#ifdef TESTS
#include "test/run_tests.hpp"
#endif

int main(int argc, char *argv[]) {
  // Built with tests?
  #ifdef TESTS
  if (argc > 0 && strcmp(argv[0], "test") == 0) {
    run_tests();
    return 0;
  }
  #endif

	hoboquest::Game g(std::cin, std::cout);
  return 0;
}


