#ifndef HOBO_ITEM_CONTAINER
#define HOBO_ITEM_CONTAINER

#include <string>

#include "item.hpp"
#include "../container.hpp"

namespace hoboquest {
  class ContainerItem : public Item, public Container {
    public:
      ContainerItem(std::string name);
      ContainerItem(std::string name, unsigned value);
      ContainerItem(std::string name, unsigned value, unsigned weight);

      virtual bool is_container() const;
  };
}

#endif
