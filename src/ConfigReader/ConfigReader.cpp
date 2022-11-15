#include "ConfigReader.hpp"

#include <iostream>

ConfigReader::ConfigReader():
    m_config()
{

}

ConfigReader::~ConfigReader() {

}

AppConfig ConfigReader::loadFromFile(char* filepath) {
    if(!m_config.loadFromFile(filepath)) {
        throw std::runtime_error("Failed to get config.\nAborting.");
    }

    RendererConfig r;
    MapConfig m;
    NetworkConfig n;

    r.windowWidth = m_config.getIntValue("RENDERER", "WINDOW_WIDTH", 640);
    r.windowHeight = m_config.getIntValue("RENDERER", "WINDOW_HEIGHT", 480);
    r.windowTitle = m_config.getValue("RENDERER", "WINDOW_TITLE");
    r.icon = m_config.getValue("RENDERER", "WINDOW_ICON");
    r.frameRate = m_config.getIntValue("RENDERER", "FRAMERATE", 15);

    m.tileFolder = m_config.getValue("MAP", "TILE_FOLDER");
    m.tilePrefix = m_config.getValue("MAP", "TILE_PREFIX");
    m.zoomLevel = m_config.getIntValue("MAP", "ZOOM_LEVEL", 0);
    m.tileCountX = m_config.getIntValue("MAP", "CHESS_X", 0);
    m.tileCountY = m_config.getIntValue("MAP", "CHESS_Y", 0);

    n.entryFile = m_config.getValue("NETWORK", "SAMPLE");

    return { r, m, n };
}