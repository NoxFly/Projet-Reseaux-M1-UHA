#include "Renderer.hpp"

#include <iostream>
#include <cmath>


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
    if(!m_guiTexture.loadFromFile("res/images/sprite_gui.png")) {
        throw std::runtime_error("[ERROR] Renderer::Renderer : Failed to load gui texture.");
    }

    m_antennaSprite.setTexture(m_guiTexture);
    m_antennaSprite.setTextureRect(sf::IntRect(29, 445, 129, 157));
    m_antennaSprite.setScale(.3, .3);

    m_locationSprite.setTexture(m_guiTexture);
    m_locationSprite.setTextureRect(sf::IntRect(0, 210, 180, 180));
    m_locationSprite.setScale(.3, .3);
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

sf::Vector2i Renderer::getPixelToWorldCoords(const sf::Vector2i& p, MapModel& map) {
    if(!m_window)
        return sf::Vector2i(0, 0);

    auto ratio = map.getCurrentRatio();

    auto winSize = (sf::Vector2i)(m_window->getSize() / (unsigned int)2);
    auto offset = winSize - map.getPosition();

    auto worldCoord = p - offset;

    auto scaledWorldCoord = sf::Vector2i(worldCoord.x / ratio, worldCoord.y / ratio);

    return scaledWorldCoord;
}

void Renderer::render(Model& model) {
    m_window->clear(m_background);

    const auto& defaultView = m_window->getDefaultView();

    auto& gui = model.getGui();

    // DEV ONLY
    // after main menu > start
    if(!gui.isDrawingFullscreenMenu()) {
        // map
        const MapModel& map = model.getMap();
        const std::vector<Tile>& tiles = map.getTiles();

        const sf::Vector2i& mapPosition = map.getPosition();

        m_view.setCenter((sf::Vector2f)mapPosition);
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





    // scale information
    const auto scaleSize = sf::Vector2f(150, 20);
    const sf::Vector2f scalePos((sf::Vector2f)m_window->getSize() - scaleSize);


    sf::RectangleShape scaleBg(scaleSize),
        scaleStrokeBot(sf::Vector2f(scaleSize.x / 2.f, 2)),
        scaleStrokeLeft(sf::Vector2f(2, 5)),
        scaleStrokeRight(sf::Vector2f(2, 5));
    
    scaleBg.setPosition(scalePos);
    scaleBg.setFillColor(sf::Color(250, 250, 250, 220));

    scaleStrokeBot.setPosition(scalePos.x + scaleSize.x / 2 - 10, scalePos.y + scaleSize.y * .6);
    scaleStrokeBot.setFillColor(sf::Color(150, 150, 150));

    scaleStrokeLeft.setPosition(scalePos.x + scaleSize.x / 2 - 10, scalePos.y + scaleSize.y * .6 - 5);
    scaleStrokeLeft.setFillColor(sf::Color(150, 150, 150));

    scaleStrokeRight.setPosition(scalePos.x + scaleSize.x - 12, scalePos.y + scaleSize.y * .6 - 5);
    scaleStrokeRight.setFillColor(sf::Color(150, 150, 150));


    m_window->draw(scaleBg);
    m_window->draw(scaleStrokeBot);
    m_window->draw(scaleStrokeLeft);
    m_window->draw(scaleStrokeRight);

    fillText("2 km", scalePos.x + 10, scalePos.y + 3, 12, sf::Color(100, 100, 100));





    // do stuff for HUD here...
    // DEV ONLY
    // main menu
    gui.draw();

    m_window->display();
}

void Renderer::fillText(const std::string& str, const sf::Vector2f& position, const int fontSize, const sf::Color& color, const sf::Uint32 style, const std::string& alignment) {
    sf::Text txt;
    txt.setFont(m_fonts.at("Roboto"));
    txt.setCharacterSize(fontSize);
    txt.setFillColor(color);
    txt.setString(str);
    txt.setPosition(position);
    txt.setStyle(style);
    
    const int bounds = txt.getGlobalBounds().width;

    if(alignment == "center") {
        txt.setOrigin(bounds / 2, 0);
    }
    else if(alignment == "right") {
        txt.setOrigin(bounds, 0);
    }

    m_window->draw(txt);
}

void Renderer::fillText(const std::string& str, const int x, const int y, const int fontSize, const sf::Color& color, const sf::Uint32 style, const std::string& alignment) {
    fillText(str, sf::Vector2f(x, y), fontSize, color, style, alignment);
}

void Renderer::drawAntennaMenu(Antenna* antenna) {
    // antenna stats
    const unsigned int precision = 2;

    const auto& antPos = antenna->getPosition().lambert();

    std::stringstream streamX, streamY, streamFreq, streamPower, streamRange;

    streamX << std::fixed << std::setprecision(precision) << antPos.x;
    streamY << std::fixed << std::setprecision(precision) << antPos.y;

    streamFreq << std::fixed << std::setprecision(precision) << antenna->getFreq();
    streamPower << std::fixed << std::setprecision(precision) << antenna->getEmitPower();
    streamRange << std::fixed << std::setprecision(precision) << antenna->getRange();

    const auto sAntPos = streamX.str() + ", " + streamY.str();
    const auto sAntFreq = streamFreq.str() + " MHz";
    const auto sAntPower = streamPower.str() + " dBm";
    const auto sAntRange = streamRange.str() + " m";
    const auto sAntAlt = std::to_string(antenna->getAltitude()) + " m";




    // menu
    auto winSize = m_window->getSize();

    unsigned int menuWidth = 400;
    unsigned int menuHeight = winSize.y;
    
    int menuX = winSize.x - menuWidth;
    int menuY = 0;

    sf::Color hoverBg(50, 50, 50, 70);
    sf::Color menuBg(230, 230, 230);

    auto hover = sf::RectangleShape(sf::Vector2f(menuX, winSize.y));
    hover.setPosition(0, 0);
    hover.setFillColor(hoverBg);

    auto bgMenu = sf::RectangleShape(sf::Vector2f(menuWidth, menuHeight));
    bgMenu.setPosition(menuX, menuY);
    bgMenu.setFillColor(menuBg);


    unsigned int menuStrokeWidth = 3;
    sf::Color menuStrokeColor(150, 150, 150);
    
    auto menuBorder = sf::RectangleShape(sf::Vector2f(menuStrokeWidth, menuHeight));
    menuBorder.setPosition(menuX, menuY);
    menuBorder.setFillColor(menuStrokeColor);

    m_window->draw(hover);
    m_window->draw(bgMenu);
    m_window->draw(menuBorder);


    int menuLabelX = menuX + 20;
    int menuLabelY = menuY + 150;
    sf::Color menuLabelColor(50, 50, 50);
    sf::Color menuValueColor(160, 160, 160);
    auto menuLabelStyle = sf::Text::Style::Bold;

    fillText("Antenne",                 menuX + menuWidth / 2,  40, 30, menuLabelColor, menuLabelStyle, "center");

    fillText("Nom : ",                  menuLabelX,             menuLabelY + 0,     15,     menuLabelColor, menuLabelStyle);
    fillText("Coordonnees : ",          menuLabelX,             menuLabelY + 50,    15,     menuLabelColor, menuLabelStyle);
    fillText("Frequence : ",            menuLabelX,             menuLabelY + 100,   15,     menuLabelColor, menuLabelStyle);
    fillText("Puissance d'emission : ", menuLabelX,             menuLabelY + 150,   15,     menuLabelColor, menuLabelStyle);
    fillText("Distance d'emission : ",  menuLabelX,             menuLabelY + 200,   15,     menuLabelColor, menuLabelStyle);
    fillText("Hauteur : ",              menuLabelX,             menuLabelY + 250,   15,     menuLabelColor, menuLabelStyle);
    fillText("Couleur : ",              menuLabelX,             menuLabelY + 300,   15,     menuLabelColor, menuLabelStyle);


    fillText(antenna->getName(),        menuLabelX + 60,             menuLabelY + 0,     15,     menuValueColor);
    fillText(sAntPos,                   menuLabelX + 130,             menuLabelY + 50,    15,     menuValueColor);
    fillText(sAntFreq,                  menuLabelX + 110,             menuLabelY + 100,   15,     menuValueColor);
    fillText(sAntPower,                 menuLabelX + 200,             menuLabelY + 150,   15,     menuValueColor);
    fillText(sAntRange,                 menuLabelX + 190,             menuLabelY + 200,   15,     menuValueColor);
    fillText(sAntAlt,                   menuLabelX + 90,             menuLabelY + 250,   15,     menuValueColor);

    const unsigned int antColorRad = 10.0;
    sf::CircleShape antColor(antColorRad);
    antColor.setFillColor(antenna->getColor());
    antColor.setOutlineColor(sf::Color(150, 150, 150));
    antColor.setOutlineThickness(2);
    antColor.setPosition(menuLabelX + 100, menuLabelY + 300);

    m_window->draw(antColor);

    (void)antenna;
}