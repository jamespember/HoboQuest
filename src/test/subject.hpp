#ifndef HOBO_TEST_SUBJECT
#define HOBO_TEST_SUBJECT

#include <memory>
#include <cassert>
#include "../util/subject.hpp"
#include "../entity.hpp"

using namespace std;
using namespace hoboquest;

void test_subject() {
  auto a = make_shared<Entity>(Entity::ACTOR, "a", "A");

  int executed = 0;

  a->observe("test", [&executed](shared_ptr<Entity> src) {
    assert(src->id() == "a");
    ++executed;
    return true;
  });

  assert(executed == 0);
  a->notify("test", a);
  assert(executed == 1);
  a->notify("test", a);
  assert(executed == 2);

  a->observe("test", [&executed](shared_ptr<Entity> src) {
    executed += 10;
    src->set_name("AA");
    return false;
  });

  assert(a->name() == "A");
  assert(executed == 2);
  a->notify("test", a);
  assert(a->name() == "AA");
  assert(executed == 13);
  a->notify("test", a);
  assert(executed == 14);

  a->observe("test", [&executed](shared_ptr<Entity> src) {
    executed += 5;
    return false;
  });

  a->observe("test", [&executed](shared_ptr<Entity> src) {
    executed -= 1;
    return true;
  });

  assert(executed == 14);
  a->notify("test", a);
  assert(executed == 19);
  a->notify("test", a);
  assert(executed == 19);

}

#endif
