#ifndef HOBO_CAT_QUEST
#define HOBO_CAT_QUEST

#include "../quest.hpp"
#include "../entity.hpp"
#include <vector>

using namespace std;

namespace hoboquest {
  class CatQuest : public Quest {
    protected:
      PtrMap<Area> &_areas;
      shared_ptr<Actor> _actor;

    public:
      CatQuest(Engine &engine,
          PtrMap<Area> &areas, shared_ptr<Actor> actor) :
      Quest("cat_quest", "The Cat Quest", engine), _areas(areas), _actor(actor) {
					place_cats();
      }
      
      void place_cats() {
      	vector<shared_ptr<Equippable>> cats;
      	vector<string> cat_ids = {"mjau", "cow", "milk", "catwoman", "curt"};
      	vector<string> cat_names = {"Mr Mjau", "Mr Cow", "Mrs Milk", "Catwoman", "Curt"};
      	vector<string> cat_areas = {"market", "floor1", "shelter", "alley", "police_station"};
      	
      	for (int x = 0; x < 5; x++) {
		    	auto cat = make_shared<Equippable>(cat_ids[x], cat_names[x]);
		      cat->set_weight(5);
		      cat->set_value(10);
		      _areas.get(cat_areas[x])->add_item(cat);
      	}
      }

      void on_start() {
      }
  };
} /* hoboquest */ 

#endif
