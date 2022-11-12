#include "MapModel.hpp"

#include <iostream>

MapModel::MapModel():
    m_config{},
    m_tiles{},
    m_zoomRatio{},
    m_currentZoomLevel(1),
    m_position(0, 0)
{

}

MapModel::~MapModel() {

}

void MapModel::loadFromConfig(const MapConfig& config) {
    m_tiles.resize(config.zoomLevel);
    m_zoomRatio.resize(config.zoomLevel-1);

    // load all levels of tiles
    for(uint i=1; i <= config.zoomLevel; i++) {  
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

    // setup ratio
    const uint maxTileSize = m_tiles.at(config.zoomLevel-1).getTileSize().x;

    for(uint i=0; i < config.zoomLevel-1; i++) {  
        auto s = m_tiles.at(i).getTileSize();
        m_zoomRatio[i] = (float)maxTileSize / s.x;
    }

    centerPosition();
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

sf::Vector2u MapModel::getMapDimension() {
    return getMapDimension(m_currentZoomLevel);
}

sf::Vector2u MapModel::getMapDimension(uint level) {
    return m_tiles.at(level-1).getDimension();
}

uint MapModel::getZoomLevel() const {
    return m_currentZoomLevel;
}

void MapModel::setZoomLevel(uint level) {
    if(level > 0 && level <= m_config.zoomLevel) {
        m_currentZoomLevel = level;
    }
}

const std::vector<Tile>& MapModel::getTiles() const {
    return m_tiles.at(m_currentZoomLevel).getTiles();
}

void MapModel::centerPosition() {
    auto dim = getMapDimension();

    m_position.x = dim.x / 2;
    m_position.y = dim.y / 2;
}

sf::Vector2f MapModel::getPosition() const {
    return m_position;
}