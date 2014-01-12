#ifndef HOBO_ENTITY
#define HOBO_ENTITY

#include "util/subject.hpp"

#include <string>
#include <iostream>

namespace hoboquest {
  class Entity;

  class Entity : public Subject<Entity>, public std::enable_shared_from_this<Entity> {
    public:
      enum Type { AREA, ITEM, ACTOR, QUEST };
      static const char* const TYPE_NAME[];

    protected:
      const Type _type;
      const std::string _id;
      std::string _name, _description;

    public:
      Entity(Type type, const std::string &id, const std::string &name) :
        _type(type), _id(id), _name(name) {}

      Type type() const { return _type; }
      const std::string & id() const { return _id; }
      const std::string & name() const { return _name; }
      const std::string & description() const { return _description; }

      void set_name(const std::string &name) {
        _name = name;
        notify("changed_name", shared_from_this());
      }
      void set_description(const std::string desc) {
        _description = desc;
        notify("changed_description", shared_from_this());
      }

      virtual void describe_short(std::ostream &out) const {
        out << _name << " (" << _id << ": " << TYPE_NAME[_type] << ")";
      }

      virtual void describe(std::ostream &out) const {
        describe_short(out);
        out << std::endl;
      }
  };

  inline std::ostream & operator << (std::ostream &out, const Entity &e) {
    e.describe_short(out);
    return out;
  }
}

#endif
