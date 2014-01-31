#include "ranger.hpp"
#include "walker.hpp"
#include "player.hpp"

#include <memory>
#include <string>
#include <iostream>

namespace hoboquest {
  Ranger::Ranger() : Walker("ranger", "Texas Ranger"),
  _spoken_with_player(false), _dropped_badge(false) {
  }

  void Ranger::init() {
    set_description("The real law man around these parts.");
    set_hp(30);
    set_damage(10);
    add_money(50);

    badge = std::make_shared<Equippable>("badge", "Ranger badge", 10, 0);
    badge->set_value(300);
    add_item(badge);
    equip(badge->id());
  
    auto self = shared_from_this();

    observe("interacted", [this, self](std::shared_ptr<Entity> e) {
      auto player = std::dynamic_pointer_cast<Player>(e);
      if (!player) return false;
 
      if (player->has_item("badge")) {
        player->listen(self, "You found my badge!");
        player->give(std::static_pointer_cast<Actor>(self), "badge");
        player->listen(self, "Here's some cash I found on a dead thug, which I totally shouldn't have taken - don't tell anyone!");
        player->add_money(100);
      } else if (!has_item("badge")) {
        player->listen(self, "I seem to have misplaced my badge, have you seen it?");
      } else {
        player->listen(self, "Howdy friend!");
      }
      return true;
    });
  }

  void Ranger::tick() {
    if (!_location) return;

    if (_location->has_actor("player")) {
      auto player = std::dynamic_pointer_cast<Player>(_location->get_actor("player"));
      auto self = shared_from_this();
      if (player->has_item("gun")) {
        player->listen(self, "Don't go about waving that gun around mister!");
      } else if (!_spoken_with_player) {
        player->listen(self, "Hey there fella! Don't cause any trouble or I'll come after you.");
        _spoken_with_player = true;
      }
    } else {
      if (!_dropped_badge && has_item("badge") && random_choice(1, 2) == 1) {
        _dropped_badge = drop("badge");
      }
    }

    _idle_turns = random_choice(1, 3);
    Walker::tick();
  }
} /* hoboquest */ 

