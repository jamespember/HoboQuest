#include "container_entity.hpp"
#include "util/ptr_map.hpp"
#include "item/item.hpp"

#include <memory>
#include <iostream>
#include <string>
#include <utility>
#include <memory>

namespace hoboquest {
  ContainerEntity::ContainerEntity(Entity::Type type, const std::string &id,
      const std::string &name) :
    Entity(type, id, name), _capacity(100), _carrying(0), _money(0) {
    if (type == AREA)
      _capacity = UNLIMITED_CAPACITY;
      // set_capacity(UNLIMITED_CAPACITY);
  }

  unsigned ContainerEntity::carrying() const {
    return _carrying;
  }
  unsigned ContainerEntity::capacity() const {
    return _capacity;
  }
  bool ContainerEntity::over_encumbered() const {
    return _carrying > _capacity;
  }
  bool ContainerEntity::has_unlimited_capacity() const {
    return _capacity == UNLIMITED_CAPACITY;
  }
  void ContainerEntity::set_capacity(unsigned capacity) {
    if (capacity > UNLIMITED_CAPACITY)
      capacity = UNLIMITED_CAPACITY;
    _capacity = capacity;
    notify("changed_capacity", shared_from_this());
  }

  unsigned ContainerEntity::money() const { return _money; }
  unsigned ContainerEntity::remove_money(unsigned amount) {
    if (amount > _money)
      amount = _money;
    _money -= amount;
    notify("removed_money", shared_from_this());
    return amount;
  }
  unsigned ContainerEntity::remove_money() { return remove_money(_money); }
  void ContainerEntity::add_money(unsigned amount) {
    notify("added_money", shared_from_this());
    _money += amount;
  }

  bool ContainerEntity::has_contents() const {
    return _money > 0 || !_items.get_map().empty();
  }

  bool ContainerEntity::has_item(const std::string &id) const {
    return _items.has(id);
  }

  std::shared_ptr<Item> ContainerEntity::get_item(const std::string &id) const {
    return _items.get(id);
  }

  bool ContainerEntity::add_item(std::shared_ptr<Item> item) {
    bool success = _items.add(item);
    if (success) {
      _carrying += item->weight();
      notify("added_item", item);
      item->notify("added_to", shared_from_this());
      if (over_encumbered())
        notify("over_encumbered", shared_from_this());
    }
    return success;
  }

  // Drops and returns item if present, otherwise returns nullptr
  std::shared_ptr<Item> ContainerEntity::remove_item(const std::string &id) {
    auto item = _items.remove(id);
    if (item != nullptr) {
      _carrying -= item->weight();
      notify("removed_item", item);
      item->notify("removed_from", shared_from_this());
    }
    return item;
  }

  void ContainerEntity::describe_carrying(std::ostream &out) const {
    out << _carrying;
    if (!has_unlimited_capacity()) {
      out << " / " << _capacity;
      if (over_encumbered())
        out << ", over encumbered";
    }
  }

  void ContainerEntity::describe_contents(std::ostream &out) const {
    if (!has_contents())
      return;
    out << "Items:" << std::endl;
    if (_money > 0)
      out << "  Cash: $" << _money << std::endl;
    for (const auto &kv : _items.get_map())
      out << "  " << *(kv.second) << std::endl;
  }

  void ContainerEntity::describe(std::ostream &out) const {
    Entity::describe(out);
    // out << "Carrying ";
    // describe_carrying(out);
    // out << std::endl;
    describe_contents(out);
  }
} /* hoboquest  */

