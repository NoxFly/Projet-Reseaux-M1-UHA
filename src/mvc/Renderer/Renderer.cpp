#include "Renderer.hpp"

#include<iostream>

Renderer::Renderer():
    m_window(nullptr),
    m_screen(sf::VideoMode::getDesktopMode()),
    m_fonts{},
    m_background(232, 234, 237),
    m_view(),
    m_cursorDefault(),
    m_cursorGrab(),
    m_cursorGrabbing(),
    m_isFullscreen(false),
    m_defaultWindowSize(0, 0)
{
    // init font(s)
    sf::Font font;

    std::string fontName = "Roboto";
    std::string fontPath = "res/fonts/Roboto-Bold.ttf";

    if(!font.loadFromFile(fontPath)) {
#ifdef DEBUG
        std::err << "Failed to load font " << fontPath << std::endl;
#endif
    }
    else {
        m_fonts[fontName] = font;
    }

    m_view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

    // init cursors
    // @warning
    // THIS DOES NOT WORK :
    // images are buggy, and the grab/grabbing cursors does not exist on the system by default.
    sf::Image grabTex;
    grabTex.loadFromFile("res/images/grab_b.png");

    sf::Image grabbingTex;
    grabbingTex.loadFromFile("res/images/grabbing_b.png");

    m_cursorDefault.loadFromSystem(sf::Cursor::Arrow);
    m_cursorGrab.loadFromPixels(grabTex.getPixelsPtr(), grabTex.getSize(), sf::Vector2u(grabTex.getSize().x/2, grabTex.getSize().y/2));
    m_cursorGrabbing.loadFromPixels(grabbingTex.getPixelsPtr(), grabbingTex.getSize(), sf::Vector2u(grabbingTex.getSize().x/2, grabbingTex.getSize().y/2));
}

Renderer::~Renderer() {
    
}



void Renderer::createWindow(const RendererConfig& config) {
    // create window
    m_window = new sf::RenderWindow(
        sf::VideoMode(config.windowWidth, config.windowHeight),
        config.windowTitle,
        sf::Style::Close | sf::Style::Titlebar
    );

    m_window->setFramerateLimit(config.frameRate);
    m_window->setKeyRepeatEnabled(false);

    // app icon
    if(config.icon.size() > 0) {
        sf::Image icon;
        icon.loadFromFile(config.icon);
        m_window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }

    // position window at center of the screen
    auto wX = m_screen.width / 2 - m_window->getSize().x / 2;
    auto wY = m_screen.height / 2 - m_window->getSize().y / 2;

    m_window->setPosition(sf::Vector2i(wX, wY));
    // ---

    m_defaultWindowSize.x = config.windowWidth;
    m_defaultWindowSize.y = config.windowHeight;

    m_view.reset(sf::FloatRect(0, 0, config.windowWidth, config.windowHeight));

    m_window->setMouseCursor(m_cursorDefault);
}


sf::RenderWindow* Renderer::getWindow() const {
    return m_window;
}

sf::RenderWindow* Renderer::getWindow() {
    return m_window;
}

bool Renderer::isClosed() const {
    return m_window == nullptr;
}

void Renderer::close() {
    if(m_window != nullptr) {
        m_window->close();
        m_window = nullptr;
    }
}


void Renderer::setFullscreen(bool full) {
    m_isFullscreen = !full;
    toggleFullscreen();
}

void Renderer::toggleFullscreen() {
    m_isFullscreen = !m_isFullscreen;

    sf::Vector2u newSize = m_isFullscreen
        ? sf::Vector2u(m_screen.width, m_screen.height)
        : m_defaultWindowSize;

    sf::Vector2i position(
        m_screen.width / 2 - newSize.x / 2,
        m_isFullscreen? 0 : m_screen.height / 2 - newSize.y / 2
    );

    m_window->setSize(newSize);
    m_window->setPosition(position);
}


void Renderer::render(Model& model) {
    m_window->clear(m_background);

    // map
    const MapModel& map = model.getMap();
    const std::vector<Tile>& tiles = map.getTiles();

    sf::Vector2i position = map.getPosition();

    const auto& defaultView = m_window->getDefaultView();

    m_view.setCenter((sf::Vector2f)position);
    m_window->setView(m_view);

    for(const Tile& t : tiles) {
        if(t.hasLoaded) {
            m_window->draw(t.tile);
        }

    // red debug grid
#ifdef TILE_DEBUG
        const auto& tileSize = map.getTileSize();

        sf::RectangleShape r;
        r.setSize((sf::Vector2f)tileSize);
        r.setPosition(t.tile.getPosition());
        r.setOutlineColor(sf::Color::Red);
        r.setOutlineThickness(1);
        r.setFillColor(sf::Color::Transparent);

        m_window->draw(r);

        std::string position = std::to_string(t.position.x) + ", " + std::to_string(t.position.y);

        fillText(position, t.tile.getPosition(), .2 * tileSize.y, sf::Color::Red);
#endif
    }


    // reset the view for 2D HUD that needs to be drawn in front of the map
    m_window->setView(defaultView);

    // do stuff for HUD here...



    m_window->display();
}

void Renderer::fillText(const std::string& str, const sf::Vector2f& position, int fontSize, const sf::Color& color) {
    sf::Text txt;
    txt.setFont(m_fonts.at("Roboto"));
    txt.setCharacterSize(fontSize);
    txt.setFillColor(color);
    txt.setString(str);
    txt.setPosition(position);

    m_window->draw(txt);
}

void Renderer::fillText(const std::string& str, int x, int y, int fontSize, const sf::Color& color) {
    fillText(str, sf::Vector2f(x, y), fontSize, color);
}