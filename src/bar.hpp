#ifndef HOBO_AREA_BAR
#define HOBO_AREA_BAR

#include "area.hpp"

#include <string>

namespace hoboquest {

	class Bar : public Area {
    public:

		protected:

		public:
      Bar(const std::string &id, const std::string &name) : Area(id, name) {}
      
  };
}

#endif
