#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <memory>
#include <SFML/Graphics.hpp>

#include "Model.hpp"


class Renderer {
	public:
        Renderer();
		~Renderer();

		void render(sf::RenderWindow* window, Model model);
};

#endif // RENDERER_HPP