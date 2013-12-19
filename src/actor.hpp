#ifndef HOBO_ACTOR
#define HOBO_ACTOR

#include <string>
#include <memory>

#include "area.hpp"
#include "container.hpp"

namespace hoboquest {

	class Area;
	
  class Actor : public Container  {
  
    protected:
      std::string _name;
      bool _active;
      int _dmg = 1;
      int _hp = 1;
      int _hp_max;
      std::shared_ptr<Area> _location;

    public:
      Actor(const std::string name);
      
      std::string get_name() const;
      void set_name(std::string name);

      void on_enter(std::shared_ptr<Area> area);
      void on_exit(std::shared_ptr<Area> area);

      void move_to(std::shared_ptr<Area> area);

      void action();
      
  };
} /* hoboquest  */ 

#endif
