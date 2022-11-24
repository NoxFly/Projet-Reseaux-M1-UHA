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
        std::cerr << "Failed to load font " << fontPath << std::endl;
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
    m_cursorDefault.loadFromSystem(sf::Cursor::Arrow);

    sf::Image grabTex, grabbingTex;

    if(grabTex.loadFromFile("res/images/grab_b.png")) {
        m_cursorGrab.loadFromPixels(grabTex.getPixelsPtr(), grabTex.getSize(), sf::Vector2u(grabTex.getSize().x/2, grabTex.getSize().y/2));    
    }

    if(grabbingTex.loadFromFile("res/images/grabbing_b.png")) {
        m_cursorGrabbing.loadFromPixels(grabbingTex.getPixelsPtr(), grabbingTex.getSize(), sf::Vector2u(grabbingTex.getSize().x/2, grabbingTex.getSize().y/2));
    }



    // load gui texture
    m_guiTexture.loadFromFile("res/images/sprite_gui.png");
    m_antennaSprite.setTexture(m_guiTexture);
    m_antennaSprite.setTextureRect(sf::IntRect(29, 445, 129, 157));
    m_antennaSprite.setScale(.3, .3);
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

#ifdef DEBUG
    std::cout << "\nNew window :\n"
        << "  Title : " << config.windowTitle
        << "\n  Resolution : " << config.windowWidth << "x" << config.windowHeight << "p"
        << "\n  Framerate : " << config.frameRate
        << "\n  Position : " << wX << ", " << wY
        << "\n" << std::endl;
#endif
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


void Renderer::setFullscreen(const bool full) {
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

    const auto& defaultView = m_window->getDefaultView();

    auto& gui = model.getGui();

    // DEV ONLY
    // after main menu > start
    if(!gui.shouldDraw()) {
        // map
        const MapModel& map = model.getMap();
        const std::vector<Tile>& tiles = map.getTiles();

        sf::Vector2i position = map.getPosition();

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



        // network
        const auto& net = model.getNetwork();

        bool showA = net.shouldShowAntennas();
        bool showR = net.shouldShowRanges();
        bool showC = net.shouldShowColors();

        sf::Color baseColor(150, 150, 150);
        sf::Color baseColorT(150, 150, 150, 50);

        if(showA || showR || showC) {
            const auto& ants = net.getAntennas();
            const float ratio = map.getCurrentRatio();
            const auto bounds = m_antennaSprite.getGlobalBounds();

            m_antennaSprite.setColor(baseColor);

            for(const auto& ant : ants) {
                const auto& position = ant.getPosition().coords();

                sf::Vector2f pos(position.x * ratio, position.y * ratio);

                if(showA) {
                    if(showC) {
                        m_antennaSprite.setColor(ant.getColor());
                    }

                    sf::Vector2f posA(pos.x - bounds.width/2, pos.y - bounds.height);

                    m_antennaSprite.setPosition(posA);

                    m_window->draw(m_antennaSprite);
                }

                if(showR) {
                    int radius = ant.getRange() * ratio;

                    sf::CircleShape range(radius, 90);

                    range.setOrigin(radius, radius);
                    range.setPosition(pos);
                    
                    range.setFillColor(baseColorT);

                    range.setOutlineThickness(2);
                    range.setOutlineColor(showC? ant.getColor() : baseColor);

                    m_window->draw(range);
                }
            }
        }

    }




    // reset the view for 2D HUD that needs to be drawn in front of the map
    m_window->setView(defaultView);

    // do stuff for HUD here...
    // DEV ONLY
    // main menu
    if(gui.shouldDraw()) {
        auto& tgui = gui.getTgui();
        tgui.draw();
    }


    m_window->display();
}

void Renderer::fillText(const std::string& str, const sf::Vector2f& position, const int fontSize, const sf::Color& color) {
    sf::Text txt;
    txt.setFont(m_fonts.at("Roboto"));
    txt.setCharacterSize(fontSize);
    txt.setFillColor(color);
    txt.setString(str);
    txt.setPosition(position);

    m_window->draw(txt);
}

void Renderer::fillText(const std::string& str, const int x, const int y, const int fontSize, const sf::Color& color) {
    fillText(str, sf::Vector2f(x, y), fontSize, color);
}