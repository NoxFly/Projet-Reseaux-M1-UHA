#include "ConfigReader.hpp"

#include <iostream>

ConfigReader::ConfigReader():
    m_config()
{

}

ConfigReader::~ConfigReader() {

}

AppConfig ConfigReader::loadFromFile(const char* filepath) {
    if(!m_config.loadFromFile(filepath)) {
        throw std::runtime_error("[ERROR] ConfigReader::loadFromFile : Failed to get config.\nAborting.");
    }

    RendererConfig r;
    MapConfig m;

    r.windowWidth   = m_config.getIntValue("RENDERER", "WINDOW_WIDTH", 640);
    r.windowHeight  = m_config.getIntValue("RENDERER", "WINDOW_HEIGHT", 480);
    r.windowTitle   = m_config.getValue("RENDERER", "WINDOW_TITLE");
    r.icon          = m_config.getValue("RENDERER", "WINDOW_ICON");
    r.frameRate     = m_config.getIntValue("RENDERER", "FRAMERATE", 15);

    m.tileFolder    = m_config.getValue("MAP", "TILE_FOLDER");
    m.tilePrefix    = m_config.getValue("MAP", "TILE_PREFIX");
    m.zoomLevel     = m_config.getIntValue("MAP", "ZOOM_LEVEL", 0);
    m.tileCountX    = m_config.getIntValue("MAP", "CHESS_X", 0);
    m.tileCountY    = m_config.getIntValue("MAP", "CHESS_Y", 0);

    m.km            = sf::Vector2f(
        m_config.getIntValue("MAP", "KM_DISTANCE_X", 0),
        m_config.getIntValue("MAP", "KM_DISTANCE_Y", 0)
    );

    m.topLeft       = sf::Vector2f(
        std::stof(m_config.getValue("MAP", "TOP_LEFT_X")),
        std::stof(m_config.getValue("MAP", "TOP_LEFT_Y"))
    );

    m.bottomRight   = sf::Vector2f(
        std::stof(m_config.getValue("MAP", "BOTTOM_RIGHT_X")),
        std::stof(m_config.getValue("MAP", "BOTTOM_RIGHT_Y"))
    );

    NetworkConfig n {};

    return { r, m, n };
}