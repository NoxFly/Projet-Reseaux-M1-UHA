#ifndef RENDERER_HPP
#define RENDERER_HPP

//#define TILE_DEBUG


#include <map>
#include <memory>
#include <SFML/Graphics.hpp>

#include "config_interfaces.hpp"
#include "Model.hpp"


class Renderer {
	public:
        Renderer();
		~Renderer();

        void createWindow(const RendererConfig& config);
		void render(Model& model);

        sf::RenderWindow* getWindow() const;
        bool isClosed() const;
        void close();

        void setFullscreen(bool full);
        void toggleFullscreen();

    protected:
		sf::RenderWindow* m_window;
        sf::VideoMode m_screen;
        std::map<std::string, sf::Font> m_fonts;
        sf::Color m_background;
        sf::View m_view;

        bool m_isFullscreen;
        sf::Vector2u m_defaultWindowSize;
};

#endif // RENDERER_HPP