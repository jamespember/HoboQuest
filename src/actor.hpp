#ifndef HOBO_ACTOR
#define HOBO_ACTOR

#include <string>
#include <memory>

#include "area.hpp"
#include "container.hpp"

namespace hoboquest {
	class Area;
	
  class Actor : public Container {
  
    protected:
      std::string _name;
      bool _active;
      int _damage = 1;
      int _hp = 1;
      int _hp_max;
      std::shared_ptr<Area> _location;

    public:
      Actor(const std::string &name);
      virtual ~Actor();
      
      std::string name() const;
      void set_name(const std::string &name);

      bool active() const;
      void set_active(bool active);

      int damage() const;
      int hp() const;
      int hp_max() const;
      void set_damage(int damage);
      void set_hp(int hp);
      void set_hp_max(int hp_max);

      virtual void on_enter(std::shared_ptr<Area> area);
      virtual void on_exit(std::shared_ptr<Area> area);

      void move_to(std::shared_ptr<Area> area);

      virtual void tick();
      
  };
} /* hoboquest  */ 

#endif
