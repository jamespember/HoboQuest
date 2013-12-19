#include <iostream>
#include <string>
#include "game.hpp"
#include "actor.hpp"
#include "area.hpp"


void actor_pointer_test() {
	auto area = std::make_shared<hoboquest::Area>("House", "A small wooden house");
	auto actor = std::make_shared<hoboquest::Actor>("Thief");

	area->add_actor(actor);
	std::cout << area->has_actor(actor->get_name()) << std::endl;
	auto test = area->get_actor(actor->get_name());

	actor->set_name("Dirty thief");

	std::cout << "Area " << area->get_name() << " has actor " << test->get_name();
	std::cout << std::endl;

	area->remove_actor(actor->get_name());
	std::cout << area->has_actor(actor->get_name()) << std::endl;
}

void area_pointer_test() {
	auto sp1 = std::make_shared<hoboquest::Area>("House", "A small wooden house");
	auto sp2 = std::make_shared<hoboquest::Area>("Garden", "A beautiful garden");

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

int main() {
	hoboquest::Game g(std::cin, std::cout);
	actor_pointer_test();

	return (0);
}


