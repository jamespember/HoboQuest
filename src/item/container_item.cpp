#include "container_item.hpp"
#include "item.hpp"
#include "../container.hpp"

#include <string>

namespace hoboquest {
  ContainerItem::ContainerItem(std::string name) : Item(name), Container() { }
  ContainerItem::ContainerItem(std::string name, unsigned value) : Item(name, value), Container() { }
  ContainerItem::ContainerItem(std::string name, unsigned value, unsigned weight) :
    Item(name, value, weight), Container() { }

  bool ContainerItem::is_container() const { return true; }
}

