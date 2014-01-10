#include <iostream>

#define TEST(NAME) \
  std::cout << "=== TESTING " << #NAME << std::endl; \
  test_ ## NAME ();
 
#include "subject.hpp"
#include "item.hpp"
#include "container.hpp"
#include "area.hpp"
#include "actor.hpp"
#include "command.hpp"
#include "commandable.hpp"
#include "player.hpp"
#include "movement.hpp"
#include "game.hpp"

using std::cout;

int run_tests() {
  cout << "=== Running test suite...\n";

  TEST(subject)
  TEST(item)
  TEST(container)
  TEST(area)
  TEST(actor)
  TEST(command)
  TEST(commandable)
  TEST(player)
  TEST(movement)
  TEST(game)

  cout << "=== All tests passed!\n";

	return 0;
}
