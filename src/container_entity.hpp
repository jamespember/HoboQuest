#ifndef HOBO_CONTAINER
#define HOBO_CONTAINER 1

#include "entity.hpp"
#include "util/ptr_map.hpp"
#include "item/item.hpp"

#include <memory>
#include <iostream>
#include <string>
#include <utility>
#include <memory>

namespace hoboquest {
  class ContainerEntity : public Entity {
    protected:
      PtrMap<Item> _items;
      unsigned _capacity, _carrying, _money;

    public:
      const unsigned UNLIMITED_CAPACITY = 10e8;

      ContainerEntity(Entity::Type type, const std::string &id, const std::string &name);

      unsigned carrying() const;
      unsigned capacity() const;
      bool over_encumbered() const;
      bool has_unlimited_capacity() const;
      void set_capacity(unsigned capacity);

      unsigned money() const;
      virtual unsigned remove_money(unsigned amount);
      unsigned remove_money();
      virtual void add_money(unsigned amount);

      bool has_contents() const;
      bool has_item(const std::string &id) const;

      std::shared_ptr<Item> get_item(const std::string &id) const;
      virtual bool add_item(std::shared_ptr<Item> item);
      virtual std::shared_ptr<Item> remove_item(const std::string &id);

      void describe_carrying(std::ostream &out) const;
      void describe_contents(std::ostream &out) const;
      virtual void describe(std::ostream &out) const;
  };
} /* hoboquest  */

#endif
