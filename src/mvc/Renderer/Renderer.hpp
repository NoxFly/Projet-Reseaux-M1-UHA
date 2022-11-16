#ifndef RENDERER_HPP
#define RENDERER_HPP

// #define TILE_DEBUG


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
        sf::RenderWindow* getWindow();

        bool isClosed() const;
        void close();

        void setFullscreen(const bool full);
        void toggleFullscreen();

    protected:
        void fillText(const std::string& str, const int x, const int y, const int fontSize=20, const sf::Color& color=sf::Color::Black);
        void fillText(const std::string& str, const sf::Vector2f& position, const int fontSize=20, const sf::Color& color=sf::Color::Black);

		sf::RenderWindow* m_window;
        sf::VideoMode m_screen;
        std::map<std::string, sf::Font> m_fonts;
        sf::Color m_background;
        sf::View m_view;
    
        sf::Cursor m_cursorDefault, m_cursorGrab, m_cursorGrabbing;

        bool m_isFullscreen;
        sf::Vector2u m_defaultWindowSize;
};

#endif // RENDERER_HPP