#ifndef HOBO_CONTAINER
#define HOBO_CONTAINER 1

#include "entity.hpp"
#include "util/ptr_map.hpp"
#include "item/item.hpp"

#include <memory>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <memory>

namespace hoboquest {
  class ContainerEntity : public Entity {
    protected:
      PtrMap<Item> _items;
      unsigned _capacity, _carrying, _money;

    public:
      const unsigned UNLIMITED_CAPACITY = 10e8;
      
      ContainerEntity(Entity::Type type, const std::string &id,
          const std::string &name) :
        Entity(type, id, name), _capacity(100), _carrying(0), _money(0) {
        if (type == AREA)
          _capacity = UNLIMITED_CAPACITY;
          // set_capacity(UNLIMITED_CAPACITY);
      }

      unsigned carrying() const { return _carrying; }
      unsigned capacity() const { return _capacity; }
      bool over_encumbered() const { return _carrying > _capacity; }
      bool has_unlimited_capacity() const { return _capacity == UNLIMITED_CAPACITY; }
      void set_capacity(unsigned capacity) {
        if (capacity > UNLIMITED_CAPACITY)
          capacity = UNLIMITED_CAPACITY;
        _capacity = capacity;
        notify("changed_capacity", shared_from_this());
      }

      unsigned money() const { return _money; }
      unsigned take_money(unsigned amount) {
        if (amount > _money)
          amount = _money;
        _money -= amount;
        notify("lost_money", shared_from_this());
        return amount;
      }
      unsigned take_money() { return take_money(_money); }
      void give_money(unsigned amount) {
        notify("got_money", shared_from_this());
        _money += amount;
      }

      bool has_contents() const {
        return _money > 0 || !_items.get_map().empty();
      }

      bool has_item(const std::string &id) const {
        return _items.has(id);
      }

      std::shared_ptr<Item> get_item(const std::string &id) const {
        return _items.get(id);
      }

      virtual bool add_item(std::shared_ptr<Item> item) {
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
      virtual std::shared_ptr<Item> remove_item(const std::string &id) {
        auto item = _items.remove(id);
        if (item != nullptr) {
          _carrying -= item->weight();
          notify("removed_item", item);
          item->notify("removed_from", shared_from_this());
        }
        return item;
      }

      void describe_carrying(std::ostream &out) const {
        out << _carrying;
        if (!has_unlimited_capacity()) {
          out << '/' << _capacity;
          if (over_encumbered())
            out << ", over encumbered";
        }
      }

      void describe_contents(std::ostream &out) const {
        if (!has_contents())
          return;
        out << "Items:" << std::endl;
        if (_money > 0)
          out << "  Cash: $" << _money << std::endl;
        for (const auto &kv : _items.get_map())
          out << "  " << *(kv.second) << std::endl;
      }

      virtual void describe(std::ostream &out) const {
        Entity::describe(out);
        // out << "Carrying ";
        // describe_carrying(out);
        // out << std::endl;
        describe_contents(out);
      }
  };
} /* hoboquest  */

#endif
