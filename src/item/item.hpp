#ifndef HOBO_ITEM
#define HOBO_ITEM

#include <string>

namespace hoboquest {
	class Item {
		protected:
			std::string _name;
			unsigned _value, _weight;

		public:
			Item(std::string name);
			Item(std::string name, unsigned value);
			Item(std::string name, unsigned value, unsigned weight);

			const std::string & name()	const;
			unsigned value()						const;
			unsigned weight()						const;
			
			const bool is_consumable() 	const;
			const bool is_equippable() 	const;
			const bool is_container()  	const;
	};
}

#endif
