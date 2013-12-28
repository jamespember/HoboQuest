#ifndef HOBO_CONTAINER
#define HOBO_CONTAINER 1

#include <memory>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <memory>
#include "item/item.hpp"

namespace hoboquest {
	class Container {
		protected:
      std::unordered_map<std::string, std::shared_ptr<Item>> _items;
      unsigned _capacity, _carrying, _money;

		public:
			Container() : _capacity(100), _carrying(0), _money(0) {}

      unsigned carrying() const { return _carrying; }
      unsigned capacity() const { return _capacity; }
      bool over_encumbered() const {
        return _carrying > _capacity;
      }

      void set_capacity(unsigned capacity) { _capacity = capacity; }

      unsigned money() const { return _money; }
      unsigned take_money(unsigned amount) {
        if (amount > _money)
          amount = _money;
        _money -= amount;
        return amount;
      }
      unsigned take_money() { return take_money(_money); }
      void give_money(unsigned amount) { _money += amount; }

			bool has_item(const std::string &name) const {
				return _items.count(name) > 0;
			}

      // Returns item or nullptr.
      std::shared_ptr<Item> get_item(const std::string &name) const {
        if (!has_item(name))
          return nullptr;
				return _items.at(name);
			}

			bool pickup(std::shared_ptr<Item> item) {
        // Already has item
        if (has_item(item->name()))
          return false;
				_items[item->name()] = item;
        _carrying += item->weight();
        return true;
			}

      // Drops and returns item if present, otherwise returns nullptr
      std::shared_ptr<Item> drop(const std::string &name) {
        std::shared_ptr<Item> item = get_item(name);
        if (item != nullptr) {
          _items.erase(name);
          _carrying -= item->weight();
        }
				return item;
			}

      friend std::ostream & operator << (std::ostream &out, const Container &c);
	};

  inline std::ostream & operator << (std::ostream &out, const Container &c) {
    out << c.carrying() << '/' << c.capacity();
    if (c.over_encumbered())
      out << " (over encumbered)";
    return out;
  }
} /* hoboquest  */ 

#endif
