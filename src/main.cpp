#include <iostream>
#include <string>
#include "game.hpp"


void area_pointer_test() {
	auto sp1 = std::make_shared<hoboquest::Area>(hoboquest::Area("House", "A small wooden house"));
	auto sp2 = std::make_shared<hoboquest::Area>(hoboquest::Area("Garden", "A beautiful garden"));

	sp1->add_exit("door", sp2);
	std::cout << sp1->has_exit("door") << " " << sp2->has_exit("door") << std::endl;
	auto exit = sp1->get_exit("door");

	sp2->set_name("Big Garden");
	sp2->set_description("An amazingly large garden");

	std::cout << "Area " << sp1->get_name() << " has exit " << exit->get_name();
	std::cout << " (" << exit->get_description() << ")" << std::endl;

	sp1->remove_exit("door");
	std::cout << sp1->has_exit("door") << " " << sp2->has_exit("door") << std::endl;	
}

// int main(int argc, char** argv) {
int main() {
	hoboquest::Game g(std::cin, std::cout);
	//area_pointer_test();

	return (0);
}


