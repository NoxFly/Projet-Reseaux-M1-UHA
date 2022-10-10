#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <memory>
#include <SFML/Graphics.hpp>

#include "Model.hpp"

/**
 * Pure Abstract class.
 * Defines the Renderer box model.
 */
class Renderer {
	public:
		virtual ~Renderer() {};

		/**
		 * Can be called to render on the given window, with its associated model.
		 */
		virtual void render(sf::RenderWindow* window) = 0;

		void bindModel(std::shared_ptr<Model> model) {
			m_model = model;
		}

	protected:
		std::weak_ptr<Model> m_model;
};

#endif // RENDERER_HPP