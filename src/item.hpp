#ifndef HOBO_ITEM
#define HOBO_ITEM

#include <string>

namespace hoboquest {
	class Item {
		protected:
			std::string _name, _type;
			unsigned _value, _weight;

		public:
			Item(std::string name, unsigned value, unsigned weight) :
        _name(name), _type("item"), _value(value), _weight(weight) {}

			Item(std::string name, unsigned value) :
        Item(name, value, 1) {}

			Item(std::string name) :
        Item(name, 1, 1) {}

			const std::string & type() const { return this->_type; }
			const std::string & name() const { return this->_name; }
			unsigned value() const { return this->_value; }
			unsigned weight() const { return this->_weight; }
	};
}

#endif
