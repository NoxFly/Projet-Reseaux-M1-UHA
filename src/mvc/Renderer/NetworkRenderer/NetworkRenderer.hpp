#ifndef NETWORKRENDERER_HPP
#define NETWORKRENDERER_HPP

#include "Renderer.hpp"

#include <SFML/Graphics.hpp>

class NetworkRenderer: public Renderer {
	public:
		NetworkRenderer();
		~NetworkRenderer();

		void render(sf::RenderWindow* window);
};

#endif // NETWORKRENDERER_HPP