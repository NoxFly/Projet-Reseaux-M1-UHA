#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <SFML/Graphics.hpp>

#include "Model.hpp"

class Controller {
	public:
        Controller();
		~Controller();

        void update(sf::RenderWindow* window, Model model, bool* running);
};

#endif // CONTROLLER_HPP