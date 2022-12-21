#include <iostream>

#include "Application.hpp"
#include "Graphe.hpp"

int main(int argc, char **argv) {
	
	auto app = std::make_unique<Application>(argc, argv);

	app->start();
	std::vector<Arrete> arretes = {
		{0,1}, {0,4}, {0,5}, {4,5}, {1,4}, {1,3}, {2,3}, {2,4}
	};
	int n = 6;
	Graphe graphe(arretes, n);
	graphe.colorationGraphe(n);

	return 0;

	return EXIT_SUCCESS;
}