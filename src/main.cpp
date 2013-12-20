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
  if (argc > 1 && strcmp(argv[1], "test") == 0)
    return run_tests();
  #endif

	hoboquest::Game g(std::cin, std::cout);
  return 0;
}


