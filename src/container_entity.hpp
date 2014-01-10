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
          set_capacity(UNLIMITED_CAPACITY);
      }

      unsigned carrying() const { return _carrying; }
      unsigned capacity() const { return _capacity; }
      bool over_encumbered() const { return _carrying > _capacity; }
      bool has_unlimited_capacity() const { return _capacity == UNLIMITED_CAPACITY; }
      void set_capacity(unsigned capacity) {
        if (capacity > UNLIMITED_CAPACITY)
          capacity = UNLIMITED_CAPACITY;
        _capacity = capacity;
      }

      unsigned money() const { return _money; }
      unsigned take_money(unsigned amount) {
        if (amount > _money)
          amount = _money;
        _money -= amount;
        return amount;
      }
      unsigned take_money() { return take_money(_money); }
      void give_money(unsigned amount) { _money += amount; }

			bool has_item(const std::string &id) const {
				return _items.has(id);
			}

      std::shared_ptr<Item> get_item(const std::string &id) const {
				return _items.get(id);
			}

			bool pickup(std::shared_ptr<Item> item) {
        bool success = _items.add(item);
        if (success)
          _carrying += item->weight();
        return success;
			}

      // Drops and returns item if present, otherwise returns nullptr
      std::shared_ptr<Item> drop(const std::string &id) {
        auto item = _items.remove(id);
        if (item != nullptr)
          _carrying -= item->weight();
				return item;
			}

      virtual void to_ostream(std::ostream &out) const {
        Entity::to_ostream(out);
        out << ", container($" << _money  << ", " << _carrying;
        if (!has_unlimited_capacity()) {
          out << '/' << _capacity;
          if (over_encumbered())
            out << ", over encumbered";
        }
        out << ')';
      }
	};
} /* hoboquest  */

#endif
