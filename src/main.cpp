#include <iostream>
#include "Application/Application.hpp"

int main(int argc, char **argv) {
	auto app = std::make_unique<Application>(argc, argv);

	app->start();

	return 0;

	return EXIT_SUCCESS;
}