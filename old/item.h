#ifndef HOBO_ITEM
#define HOBO_ITEM

#include <string>

namespace hoboquest {
	class Item {
		protected:
			std::string _name, _type;
			int _value;

		public:
			Item(std::string n) : _name(n), _value(0), _type("item") {}
			Item(std::string n, int v) : _name(n), _value(v), _type("item") {}

			std::string type() const { return _type; }
			std::string name() const { return _name; }
			int value() const { return _value; }
	};
}

#endif
