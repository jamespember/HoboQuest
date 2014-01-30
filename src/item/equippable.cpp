#include "equippable.hpp"
#include "item.hpp"
#include "../actor/actor.hpp"

#include <string>

namespace hoboquest {
    Equippable::Equippable(const std::string &id, const std::string &name,
        int hp_max_mod, int dmg_mod) :
      Item(id, name), hp_max_mod(hp_max_mod), damage_mod(dmg_mod) {}

    Equippable::Equippable(const std::string &id, const std::string &name) :
      Item(id, name), hp_max_mod(0), damage_mod(0) {}

    bool Equippable::is_equippable() const { return true; }

    void Equippable::on_equip(std::shared_ptr<Actor> actor) {
      actor->set_hp_max(actor->hp_max() + hp_max_mod);
      actor->set_damage(actor->damage() + damage_mod);
    }
    void Equippable::on_unequip(std::shared_ptr<Actor> actor) {
      actor->set_hp_max(actor->hp_max() - hp_max_mod);
      actor->set_damage(actor->damage() - damage_mod);
    }

    void Equippable::describe(std::ostream &out) const {
      Item::describe(out);
      if (hp_max_mod != 0)
        out << "  " << (hp_max_mod < 0 ? '-' : '+') << hp_max_mod << " max hp" << std::endl;
      if (damage_mod != 0)
        out << "  " << (damage_mod < 0 ? '-' : '+') << damage_mod << " damage" << std::endl;
    }
}

