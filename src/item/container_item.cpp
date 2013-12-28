#include "container_item.hpp"
#include "item.hpp"
#include "../container.hpp"

#include <string>

namespace hoboquest {
  ContainerItem::ContainerItem(std::string name, std::string description) : Item(name, description), Container() { }

  bool ContainerItem::is_container() const { return true; }
}

