#ifndef HOBO_ITEM
#define HOBO_ITEM

#include <string>

namespace hoboquest {
	class Item {
		protected:
			std::string _name, _type;
			unsigned _value, _weight;

		public:
			Item(std::string n) : _name(n), _type("item"), _value(0), _weight(1) {}
			Item(std::string n, int v) : _name(n), _type("item"), _value(v), _weigth(1) {}

			const std::string & type() const { return this->_type; }
			const std::string & name() const { return this->_name; }
			unsigned value() const { return this->_value; }
			unsigned weight() const { return this->_weight; }
	};
}

#endif
