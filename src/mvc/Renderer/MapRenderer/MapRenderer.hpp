#ifndef MAPRENDERER_HPP
#define MAPRENDERER_HPP

#include "Renderer.hpp"

#include <SFML/Graphics.hpp>

class MapRenderer: public Renderer {
	public:
		MapRenderer();
		~MapRenderer();

		void render(sf::RenderWindow* window);
};

#endif // MAPRENDERER_HPP