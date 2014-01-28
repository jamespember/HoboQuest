#ifndef HOBO_ITEM_EQUIPPABLE
#define HOBO_ITEM_EQUIPPABLE

#include <string>

#include "item.hpp"

namespace hoboquest {
  class Actor;

  class Equippable : public Item {
    public:
      const int hp_max_mod, damage_mod;

      Equippable(const std::string &id, const std::string &name, int hp_max_mod, int dmg_mod);
      Equippable(const std::string &id, const std::string &name);

      virtual bool is_equippable() const;

      virtual void on_equip(std::shared_ptr<Actor> actor);
      virtual void on_unequip(std::shared_ptr<Actor> actor);

      void describe(std::ostream &out) const;
  };
}

#endif
