#ifndef HOBO_ACTOR
#define HOBO_ACTOR

#include "container_entity.hpp"
#include "area.hpp"
#include "item/equippable.hpp"

#include <string>
#include <memory>

namespace hoboquest {
	class Area;

  class Actor : public ContainerEntity {

    protected:
      bool _alive;
      int _damage = 1;
      int _hp = 1;
      int _hp_max;
      std::shared_ptr<Area> _location;
      PtrMap<Equippable> _equipped;

    public:
      Actor(const std::string &id, const std::string &name);
      virtual ~Actor();

      bool alive() const;
      int hp() const;
      int hp_max() const;
      int modify_hp(int modifier);
      void set_hp(int hp);
      void set_hp_max(int hp_max);
      void set_damage(int damage);
      int damage() const;

      const std::shared_ptr<Area> location() const;
      std::shared_ptr<Area> location();
      const std::shared_ptr<Equippable> get_equipment(const std::string &what) const;

      virtual void tick();
      bool kill();

      void move_to(std::shared_ptr<Area> area);

      virtual std::shared_ptr<Item> remove_item(const std::string &id);

      bool go(const std::string &where);
      bool consume(const std::string &what);
      bool pickup(const std::string &what);
      bool drop(const std::string &what);
      bool equip(const std::string &what);
      bool unequip(const std::string &what);

      virtual void on_interact(std::shared_ptr<Actor> actor);
      virtual void on_death();

      virtual void describe(std::ostream &out) const;

  };
} /* hoboquest  */

#endif
