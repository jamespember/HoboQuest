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

  assert(q->state() == INACTIVE);
  assert(q->started() == false);
  assert(q->completed() == false);

  // q->describe(cout);

  q->progress("Take your first steps.");
  assert(q->state() == INACTIVE);
  assert(q->started() == false);
  assert(q->completed() == false);

  assert(q->start() == true);
  assert(q->state() == STARTED);
  assert(q->started() == true);
  assert(q->completed() == false);

  // q->describe(cout);

  q->progress("Carry on then.");
  assert(q->state() == PROGRESSED);
  assert(q->started() == true);
  assert(q->completed() == false);

  // q->describe(cout);

  assert(q->complete() == true);
  assert(q->state() == COMPLETED);
  assert(q->completed() == true);

  // q->describe(cout);

  assert(q->complete() == false);
}

#endif
