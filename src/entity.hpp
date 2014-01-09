#ifndef HOBO_ENTITY
#define HOBO_ENTITY

#include <string>
#include <iostream>

namespace hoboquest {
  class Entity {
    public:
      enum Type { AREA, ITEM, ACTOR };

    protected:
      const Type _type;
      const std::string _id;
      std::string _name;

    public:
      Entity(Type type, const std::string &id, const std::string &name) :
        _type(type), _id(id), _name(name) {}

      Type type() const { return _type; }
      const std::string & id() const { return _id; }
      const std::string & name() const { return _name; }

      void set_name(const std::string &name) {	_name = name; }

      virtual void to_ostream(std::ostream &out) const {
        out << _id << " (" << _name << ")";
      }
  };

  inline std::ostream & operator << (std::ostream &out, const Entity &e) {
    e.to_ostream(out);
    return out;
  }
}

#endif
