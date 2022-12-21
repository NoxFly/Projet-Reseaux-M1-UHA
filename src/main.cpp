// Visual Studio configuration

#pragma warning( disable : 4244 )
#pragma warning( disable : 4996 )
#pragma warning( disable : 4305 )

//


#include <iostream>


#include "Application/Application.hpp"

int main(int argc, char **argv) {
	auto app = std::make_unique<Application>(argc, argv);

	app->start();

	return EXIT_SUCCESS;
}