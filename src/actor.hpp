#ifndef HOBO_ACTOR
#define HOBO_ACTOR

#include "container_entity.hpp"
#include "area.hpp"

#include <string>
#include <memory>

namespace hoboquest {
	class Area;

  class Actor : public ContainerEntity {

    protected:
      bool _active;
      int _damage = 1;
      int _hp = 1;
      int _hp_max;
      std::shared_ptr<Area> _location;

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

      virtual void tick();

      void move_to(std::shared_ptr<Area> area);

      virtual void describe(std::ostream &out) const;

  };
} /* hoboquest  */

#endif
