#ifndef HOBO_ITEM
#define HOBO_ITEM

#include <string>

namespace hoboquest {
	class Item {
		public:
				enum Type {
					Equippable,
					Container,
					Consumable
				};

		protected:
			std::string _name;
			Item::Type _type;
			unsigned _value, _weight;

		public:
			Item(std::string name, unsigned value, unsigned weight);
			Item(std::string name, unsigned value);
			Item(std::string name);

			const Item::Type & type() const;
			const std::string & name() const;
			unsigned value() const;
			unsigned weight() const;
	};
}

#endif
