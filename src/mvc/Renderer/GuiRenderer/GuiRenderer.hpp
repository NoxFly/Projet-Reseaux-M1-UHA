#ifndef GUIRENDERER_HPP
#define GUIRENDERER_HPP

#include "Renderer.hpp"

#include <SFML/Graphics.hpp>

class GuiRenderer: public Renderer {
	public:
		GuiRenderer();
		~GuiRenderer();

		void render(sf::RenderWindow* window);
};

#endif // GUIRENDERER_HPP