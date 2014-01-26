#ifndef HOBO_GUN_QUEST
#define HOBO_GUN_QUEST

#include "../quest.hpp"

using namespace std;

namespace hoboquest {
  class GunQuest : public Quest {
    protected:
      shared_ptr<Equippable> gun;
      shared_ptr<Area> location;
      shared_ptr<Actor> actor;

    public:
      GunQuest(Engine &engine,
          shared_ptr<Area> location, shared_ptr<Actor> actor) :
      Quest("gun_quest", "Missing sidearm", engine),
      location(location), actor(actor) {
        progress(actor->name() + " is missing his precious sidearm, you should look for it.");

        gun = make_shared<Equippable>("gun", "Gun");
        gun->set_weight(2);
        gun->set_value(100);
        
        location->add_item(gun);
      }

      void on_start() {
        gun->observe("added", [this](shared_ptr<Entity> e) {
          if (e != this->_engine.player)
            return true;
          this->progress("This might be the gun " + actor->name() + " was missing.");
          return false;
        });

        actor->observe("added_item", [this](shared_ptr<Entity> e) {
          if (e != gun)
            return true;
          this->complete();
          return false;
        });
      }
  };
} /* hoboquest */ 

#endif
