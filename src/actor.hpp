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
      
      bool active() const;
      void set_active(bool active);

      int damage() const;
      int hp() const;
      int hp_max() const;
      void set_damage(int damage);
      void set_hp(int hp);
      void set_hp_max(int hp_max);

      const std::shared_ptr<Area> location() const;
      std::shared_ptr<Area> location();

      virtual void on_enter(std::shared_ptr<Area> area);
      virtual void on_exit(std::shared_ptr<Area> area);

      void move_to(std::shared_ptr<Area> area);

      virtual void tick();
      
  };
} /* hoboquest  */ 

#endif
