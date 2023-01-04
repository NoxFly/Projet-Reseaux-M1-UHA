#include "MapModel.hpp"

#include "mvc/Model/Network/Antenna/GeoPosition/GeoPosition.hpp"

#include <iostream>


MapModel::MapModel():
    m_config{},
    m_tiles{},
    m_zoomRatio{},
    m_currentZoomLevel(1),
    m_grabbing(false),
    m_oldPosition(0, 0),
    m_grabPoint(0, 0),
    m_position(0, 0)
{

}

MapModel::~MapModel() {

}

void MapModel::loadFromConfig(const MapConfig& config) {
    m_config = config;
    m_tiles.resize(config.zoomLevel);
    m_zoomRatio.resize(config.zoomLevel);

    // load all levels of tiles
    for(unsigned int i=1; i <= config.zoomLevel; i++) {  
        const std::string si = std::to_string(i);
        const std::string folder = config.tileFolder + "/level_" + si;
        const std::string prefix = config.tilePrefix + si;

#ifdef DEBUG
        std::string result = "Failed.";

        std::cout << "Loading tiles for map level " << si << "..." << std::flush;

        if(m_tiles[i-1].load(folder, prefix, ".png", config.tileCountX, config.tileCountY)) {
            result = "Done.";
        }

        std::cout << " " << result << std::endl;

#else
        m_tiles[i-1].load(folder, prefix, ".png", config.tileCountX, config.tileCountY);
#endif
    }

#ifdef DEBUG
    std::cout << std::endl;
#endif

    // setup ratio
    const unsigned int maxTileSize = m_tiles.at(config.zoomLevel-1).getTileSize().x;

    for(unsigned int i=0; i < config.zoomLevel-1; i++) {  
        auto s = m_tiles.at(i).getTileSize();
        m_zoomRatio[i] = (float)s.x / maxTileSize;
    }

    m_zoomRatio[config.zoomLevel-1] = 1;

    GeoPosition::defineMapLBT(config.topLeft, config.bottomRight, m_tiles.at(config.zoomLevel-1).getDimension());

    centerPosition();
}

const TileMap& MapModel::getTilesOfLevel(const unsigned int level) const {
    return m_tiles.at(level-1);
}

TileMap& MapModel::getTilesOfLevel(const unsigned int level) {
    return m_tiles.at(level-1);
}

unsigned int MapModel::getZoomLevels() const {
    return m_config.zoomLevel;
}

sf::Vector2u MapModel::getBoardDimension() const {
    return sf::Vector2u(m_config.tileCountX, m_config.tileCountY);
}

sf::Vector2u MapModel::getMapDimension() const {
    return getMapDimension(m_currentZoomLevel);
}

sf::Vector2u MapModel::getMapDimension(const unsigned int level) const {
    return m_tiles.at(level-1).getDimension();
}

float MapModel::getCurrentRatio() const {
    return m_zoomRatio.at(m_currentZoomLevel-1);
}

float MapModel::pxToKm(unsigned int px) const {
    // for now we don't care of complex vectors, a length is considered here with X-Axis
    // because the map is square.
    return px / (float)getMapDimension().x * m_config.km.x;
}

float MapModel::kmToPx(float km) const {
    // for now we don't care of complex vectors, a length is considered here with X-Axis
    // because the map is square.
    return km / m_config.km.x * getMapDimension().x;
}

unsigned int MapModel::getZoomLevel() const {
    return m_currentZoomLevel;
}

void MapModel::setZoomLevel(const unsigned int level) {
    if(level > 0 && level <= m_config.zoomLevel) {
        const auto oldPos = m_position;
        const auto oldDim = getMapDimension();
        
        m_currentZoomLevel = level;

        const auto newDim = getMapDimension();
        
        const auto newPos = sf::Vector2i(
            (float)oldPos.x / oldDim.x * newDim.x,
            (float)oldPos.y / oldDim.y * newDim.y
        );

        m_oldPosition = newPos;

        clampPosition();
        
        m_oldPosition = m_position;
    }
}

const std::vector<Tile>& MapModel::getTiles() const {
    return m_tiles.at(m_currentZoomLevel-1).getTiles();
}

const sf::Vector2u& MapModel::getTileSize() const {
    return m_tiles.at(m_currentZoomLevel-1).getTileSize();
}

void MapModel::centerPosition() {
    auto dim = getMapDimension();

    m_position.x = dim.x / 2;
    m_position.y = dim.y / 2;

    m_oldPosition = m_position;
}

const sf::Vector2i& MapModel::getPosition() const {
    return m_position;
}

void MapModel::setPosition(const sf::Vector2i& position) {
    m_position = position;
    m_oldPosition = m_position;
}

void MapModel::setPosition(const unsigned int x, const unsigned int y) {
    m_position = sf::Vector2i(x, y);
    m_oldPosition = m_position;
}

void MapModel::zoomIn() {
    if(m_currentZoomLevel < m_config.zoomLevel) {
        setZoomLevel(m_currentZoomLevel+1);
    }
}

void MapModel::zoomOut() {
    if(m_currentZoomLevel > 1) {
        setZoomLevel(m_currentZoomLevel-1);
    }
}

void MapModel::move(const sf::Vector2i& position) {
    m_position.x += position.x;
    m_position.y += position.y;
}

void MapModel::move(const unsigned int x, const unsigned int y) {
    m_position.x += x;
    m_position.y += y;
}

void MapModel::grab(const sf::Vector2i& mouse) {
    if(!m_grabbing) {
        m_grabPoint = mouse;
        m_grabbing = true;
    }
}

void MapModel::ungrab() {
    if(m_grabbing) {
        m_grabPoint = sf::Vector2i(0, 0);
        m_oldPosition = m_position;
        m_grabbing = false;
    }
}

void MapModel::grabMove(const sf::Vector2i& mouse) {
    if(m_grabbing) {
        clampPosition(mouse);
    }
}

void MapModel::clampPosition() {
    clampPosition(sf::Vector2i(0, 0));
}

void MapModel::clampPosition(const sf::Vector2i& mouse) {
    auto limit = getMapDimension();

    m_position.x = std::clamp(m_oldPosition.x + m_grabPoint.x - mouse.x, 0, (int)limit.x);
    m_position.y = std::clamp(m_oldPosition.y + m_grabPoint.y - mouse.y, 0, (int)limit.y);
}