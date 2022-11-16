#include <iostream>

#include "Application.hpp"

int main(int argc, char **argv) {
	auto app = std::make_unique<Application>(argc, argv);

	app->start();

	return EXIT_SUCCESS;
}