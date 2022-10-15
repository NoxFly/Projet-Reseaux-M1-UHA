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

    MapConfig m;
    NetworkConfig n;

    m.tileFolder = m_config.getValue("MAP", "TILE_FOLDER");
    m.tileSuffix = m_config.getValue("MAP", "TILE_SUFFIX");
    m.zoomLevel = m_config.getIntValue("MAP", "ZOOM_LEVEL", 0);
    m.tileCountX = m_config.getIntValue("MAP", "CHESS_X", 0);
    m.tileCountY = m_config.getIntValue("MAP", "CHESS_Y", 0);

    n.entryFile = m_config.getValue("NETWORK", "SAMPLE");

    return { m, n };
}