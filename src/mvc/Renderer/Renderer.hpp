#ifndef RENDERER_HPP
#define RENDERER_HPP

// #define TILE_DEBUG


#include <map>
#include <memory>
#include <SFML/Graphics.hpp>

#include "config_interfaces.hpp"
#include "mvc/Model/Model.hpp"


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

        sf::Vector2i getPixelToWorldCoords(const sf::Vector2i& p, MapModel& map);

        void drawAntennaMenu(const MapModel& map, Antenna* antenna);

    protected:
        void fillText(const std::string& str, const int x, const int y, const int fontSize=20, const sf::Color& color=sf::Color::Black, const sf::Uint32 style=0, const std::string& alignment="left");
        void fillText(const std::string& str, const sf::Vector2f& position, const int fontSize=20, const sf::Color& color=sf::Color::Black, const sf::Uint32 style=0, const std::string& alignment="left");

        void drawAntenna(const MapModel& map, Antenna* antenna, bool showAntenna, bool showColor, bool showRange, bool dark);
        void drawShortcuts();

		sf::RenderWindow* m_window;
        sf::VideoMode m_screen;
        std::map<std::string, sf::Font> m_fonts;
        sf::Color m_background, m_baseAntennaColor, m_baseAntennaColorDarkTransparent, m_baseAntennaColorLightTransparent;
        sf::View m_view;
    
        sf::Cursor m_cursorDefault, m_cursorGrab, m_cursorGrabbing;
        
        // dev
        sf::Texture m_guiTexture;
        sf::Sprite m_antennaSprite, m_locationSprite;
        //

        bool m_isFullscreen;
        sf::Vector2u m_defaultWindowSize;
};

#endif // RENDERER_HPP