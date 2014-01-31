#ifndef HOBO_CAT_QUEST
#define HOBO_CAT_QUEST

#include "../quest.hpp"
#include "../entity.hpp"
#include <vector>

using namespace std;

namespace hoboquest {
  class CatQuest : public Quest {
    protected:
      PtrMap<Area> _areas;
      shared_ptr<Actor> _actor;
      vector<string> _cat_ids = {"mjau", "cow", "milk", "catwoman", "curt"};
      vector<string> _cat_names = {"Mr Mjau", "Mr Cow", "Mrs Milk", "Catwoman", "Curt"};
      vector<string> _cat_areas = {"market", "floor2", "shelter", "alley", "cell"};

    public:
      CatQuest(Engine &engine,
          PtrMap<Area> areas, shared_ptr<Actor> actor) :
      Quest("cat_quest", "Finding Cat Quest", engine), _areas(areas), _actor(actor) {
        place_cats();
      }
      
      void place_cats() {       
        for (int x = 0; x < _cat_ids.size(); ++x) {
          auto cat = make_shared<Equippable>(_cat_ids[x], _cat_names[x]);
          cat->set_weight(5);
          cat->set_value(10);
          _areas.get(_cat_areas[x])->add_item(cat);
        }
      }

      void on_complete() {
        for (string cat : _cat_ids) {
          _engine.player->give(_actor, cat);
        }
        _engine.player->add_money(600);
        Quest::on_complete();
      }

      bool has_all_cats() {
        for (string cat : _cat_ids) {
          if (!_engine.player->has_item(cat)) {
            return false;
          }
        }
        return true;
      }
  };
} /* hoboquest */ 

#endif
