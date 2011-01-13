#include <stdlib.h>
#include <iostream>
#include "hoboquest/container.h"
#include "hoboquest/item.h"

using hoboquest::Container;
using hoboquest::Item;

int main(int argc, char** argv) {
	//Game g(stdin, stdout);
	Container c();
	Item it("key");
	c.pickup(it);
	std::cout << (c.has("key") == it) << std::endl;
	std::cout << (c.drop("key") == it) << std::endl;
	return (EXIT_SUCCESS);
}
