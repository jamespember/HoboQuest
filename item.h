#include <string>
#include <map>

namespace hoboquest {
	class Item {
		protected:
			std::string name;
			int value;

		public:
			Item(std::string n) : name(n), value(0) {}
			Item(std::string n, int v) : name(n), value(v) {}

			std::string name() const { return name; }
			int value() const { return value; }
	};
}

