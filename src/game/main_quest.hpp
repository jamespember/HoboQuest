#ifndef HOBO_MAIN_QUEST
#define HOBO_MAIN_QUEST

#include "../quest.hpp"

#include <string>

using namespace std;

namespace hoboquest {
  class MainQuest : public Quest {
    protected:
      shared_ptr<Actor> realtor;
      shared_ptr<Area> apartment, hall;
      shared_ptr<Player> player;

    public:
      MainQuest(Engine &engine,
          shared_ptr<Actor> realtor, shared_ptr<Area> apartment, shared_ptr<Area> hall) :
      Quest("main_quest", "Acquire living space", engine),
      realtor(realtor), apartment(apartment), hall(hall) {
        player = _engine.player;
        progress("Fulfill your biggest dream by acquiring someplace to live.");

        player->observe("added_money", [this](shared_ptr<Entity> e) {
          if (this->has_enough_money()) {
            this->progress("You've got a nice pile of cash now, it's time to start looking for a place to buy!");
            return false;
          }
          return true;
        });

        realtor->observe("interacted", [this](shared_ptr<Entity> e) {
          if (this->has_enough_money() && !this->hall->has_exit("east")) {
            this->say("Hey pal, I'm sure you want to buy one of these fine apartments!");
            this->say("It's only $1000, pe(s)ts are optional.");
            this->say("Nice, it's located on the first floor.");
            this->say("Thanks for the deal sucker, see you later!");
            this->realtor->add_money(this->player->remove_money(1000));
            this->complete();
          } else if (this->completed()) {
            this->say("I hope you like your new apartment!");
          } else {
            this->say("Come back when you got some money, punk!");
          }
          return true;
        });
      }

      bool has_enough_money() const {
        return player->money() >= 1000;
      }

      void say(const string &what) const {
        _engine.talk(realtor, what);
      }

      void on_start() {
        Quest::on_start();
      }

      void on_complete() {
        hall->add_exit("east", apartment);
        apartment->observe("on_enter", [this](shared_ptr<Entity> e) {
          if (e != player) return true;
          player->message("You've completed the game by acquiring a living space!");
          player->message("Welcome to your new apartment!");
          player->message("A hero is you!");
          _engine.quit();
          return false;
        });

        Quest::on_complete();
      }
  };
} /* hoboquest */ 

#endif
