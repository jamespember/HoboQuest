#ifndef HOBO_ITEM
#define HOBO_ITEM

#include <string>

namespace hoboquest {
	class Item {
		protected:
			std::string _name;
			int _value;

		public:
			Item(std::string n) : _name(n), _value(0) {}
			Item(std::string n, int v) : _name(n), _value(v) {}

			std::string name() const { return _name; }
			int value() const { return _value; }
	};
}

#endif
