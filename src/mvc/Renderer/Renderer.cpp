#include "Renderer.hpp"


Renderer::Renderer():
    m_window(nullptr),
    m_screen(sf::VideoMode::getDesktopMode()),
    m_fonts{},
    m_background(232, 234, 237),
    m_view(),
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
}


sf::RenderWindow* Renderer::getWindow() const {
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
    const TileMap& tiles = map.getTilesOfLevel(1);

    sf::Vector2f position = map.getPosition();
    
    m_view.setCenter(position);
    m_window->setView(m_view);

    for(const Tile& t : tiles.getTiles()) {
        if(t.hasLoaded) {
            m_window->draw(t.tile);
        }

    // red debug grid
#ifdef TILE_DEBUG
        sf::RectangleShape r;
        r.setSize((sf::Vector2f)tiles.getTileSize());
        r.setPosition(t.tile.getPosition());
        r.setOutlineColor(sf::Color::Red);
        r.setOutlineThickness(1);
        r.setFillColor(sf::Color::Transparent);

        m_window->draw(r);

        std::string position = std::to_string(t.position.x) + ", " + std::to_string(t.position.y);

        sf::Text txt;
        txt.setFont(m_fonts.at("Roboto"));
        txt.setCharacterSize(.2 * tiles.getTileSize().y);
        txt.setFillColor(sf::Color::Red);
        txt.setString(position);
        txt.setPosition(t.tile.getPosition());

        m_window->draw(txt);
#endif
    }


    m_window->display();
}