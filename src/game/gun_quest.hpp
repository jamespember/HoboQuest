#ifndef HOBO_GUN_QUEST
#define HOBO_GUN_QUEST

#include "../quest.hpp"

namespace hoboquest {
  class GunQuest : public Quest {
    public:
      GunQuest(std::shared_ptr<Area> location) :
      Quest("gun_quest", "Missing sidearm") {
        advance("Some incompetent cop is missing his precious sidearm, you should look for it.");

        auto gun = std::make_shared<Equippable>("gun", "Gun");
        gun->set_weight(2);
        gun->set_value(100);
        
        location->add_item(gun);

        gun->observe("added", [this](shared_ptr<Entity> e) {
          if (e.id() != "player")
            return true;
          this->advance("This might be the gun the cop was missing.");
          return false;
        });

        cop->observe("added_item", [this](shared_ptr<Entity> e) {
          if (e.id() != "gun")
            return true;
          this->complete();
        }):
      }
  };
} /* hoboquest */ 

#endif
