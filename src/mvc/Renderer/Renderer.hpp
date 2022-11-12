#ifndef RENDERER_HPP
#define RENDERER_HPP

//#define TILE_DEBUG


#include <map>
#include <memory>
#include <SFML/Graphics.hpp>

#include "Model.hpp"


class Renderer {
	public:
        Renderer();
		~Renderer();

		void render(sf::RenderWindow* window, Model& model);

    protected:
        std::map<std::string, sf::Font> m_fonts;
        sf::Color m_background;
};

#endif // RENDERER_HPP