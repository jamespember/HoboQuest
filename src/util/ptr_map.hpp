#ifndef HOBO_PTR_MAP
#define HOBO_PTR_MAP

#include <memory>
#include <iostream>
#include <string> 
#include <unordered_map>

namespace hoboquest {
  template <class ObjectT>
  class PtrMap {
    public:
      typedef std::unordered_map<std::string, std::shared_ptr<ObjectT>> map_type;
    protected:
      map_type _objects;

    public:
      const map_type & get_map() const {
        return _objects;
      }

			bool has(const std::string &id) const {
				return _objects.count(id) > 0;
			}

      std::shared_ptr<ObjectT> get(const std::string &id) const {
				return has(id) ? _objects.at(id) : nullptr;
			}

			bool add(std::shared_ptr<ObjectT> obj) {
        // Already has obj?
        if (has(obj->id()))
          return false;
				_objects[obj->id()] = obj;
        return true;
			}

      std::shared_ptr<ObjectT> remove(const std::string &id) {
        std::shared_ptr<ObjectT> item = get(id);
        if (item != nullptr)
          _objects.erase(id);
				return item;
			}
  };

  template <class ObjectT>
  inline std::ostream & operator << (std::ostream &out, const PtrMap<ObjectT> &m) {
    for (const auto &kv : m.get_map())
      out << "  " << kv.first << ": " << kv.second << std::endl;
    return out;
  }
} /* hoboquest */ 

#endif
