#include <string>
#include <map>

namespace hoboquest {
	class Item {
		protected:
			string name;
			int value;
		public:
			Item(string n) : name(n), value(0) {}
			Item(string n, int v) : name(n), value(v) {}

			string name() const { return name; }
			int value() const { return value; }
	}
}

