#include "MapModel.hpp"

#include <iostream>

MapModel::MapModel():
    m_config{},
    m_tiles{}
{

}

MapModel::~MapModel() {

}

void MapModel::loadFromConfig(const MapConfig& config) {
    m_tiles.resize(config.zoomLevel);

    for(uint i=1; i <= (uint)config.zoomLevel; i++) {  
        const std::string si = std::to_string(i);
        const std::string folder = config.tileFolder + "/level_" + si;
        const std::string prefix = config.tilePrefix + si;

        std::string result = "Failed.";

        std::cout << "Loading tiles for map level " << si << "..." << std::flush;
        
        if(m_tiles[i-1].load(folder, prefix, ".png", config.tileCountX, config.tileCountY)) {
            result = "Done.";
        }

        std::cout << " " << result << std::endl;
    }
}

const TileMap& MapModel::getTilesOfLevel(uint level) const {
    return m_tiles.at(level-1);
}

TileMap& MapModel::getTilesOfLevel(uint level) {
    return m_tiles.at(level-1);
}

uint MapModel::getZoomLevels() {
    return m_config.zoomLevel;
}

sf::Vector2u MapModel::getBoardDimension() {
    return sf::Vector2u(m_config.tileCountX, m_config.tileCountY);
}