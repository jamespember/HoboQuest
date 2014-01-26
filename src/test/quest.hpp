#ifndef HOBO_TEST_QUEST
#define HOBO_TEST_QUEST

#include <memory>
#include <cassert>
#include "../quest.hpp"
#include "../engine.hpp"
#include "../entity.hpp"

using namespace std;
using namespace hoboquest;

void test_quest() {
  Engine eng(cin, cout);
  auto q = make_shared<Quest>("q", "THe Hunt for Red October", eng);

  assert(q->state() == 0);
  assert(q->completed() == false);

  // q->describe(cout);

  q->advance("Take your first steps.");
  assert(q->state() == 1);
  assert(q->completed() == false);

  // q->describe(cout);

  q->advance("Carry on then.");
  assert(q->state() == 2);
  assert(q->completed() == false);

  // q->describe(cout);

  assert(q->complete() == true);
  assert(q->state() == 999);
  assert(q->completed() == true);

  // q->describe(cout);

  assert(q->complete() == false);
}

#endif
