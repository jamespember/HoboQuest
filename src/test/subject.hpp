#ifndef HOBO_TEST_SUBJECT
#define HOBO_TEST_SUBJECT

#include <memory>
#include <cassert>
#include "../util/subject.hpp"
#include "../entity.hpp"

using namespace std;
using namespace hoboquest;

void test_subject() {
  Entity a(Entity::ACTOR, "a", "A");

  int executed = 0;

  a.observe("test", [&executed](Entity &src) {
    cout << "test observed from a\n";
    ++executed;
    return true;
  });

  assert(executed == 0);
  a.notify("test", a);
  assert(executed == 1);
  a.notify("test", a);
  assert(executed == 2);

  a.observe("test", [&executed](Entity &src) {
    cout << "another test observed from a\n";
    executed += 10;
    return false;
  });

  assert(executed == 2);
  a.notify("test", a);
  assert(executed == 13);
  a.notify("test", a);
  assert(executed == 14);

}

#endif
