#include <iostream>
#include <string>
#include "game.hpp"


void area_pointer_test() {
	hoboquest::Area a("House", "A small wooden house");
	hoboquest::Area b("Garden", "A beautiful garden");
	auto sp1 = std::make_shared<hoboquest::Area>(b);
	a.add_exit("door", sp1);
	std::cout << a.has_exit("door") << " " << b.has_exit("door") << std::endl;
	//a.remove_exit("door");
	//std::cout << a.has_exit("door") << " " << b.has_exit("door") << std::endl;	
	
}

// int main(int argc, char** argv) {
int main() {
	hoboquest::Game g(std::cin, std::cout);
	area_pointer_test();

	return (0);
}


