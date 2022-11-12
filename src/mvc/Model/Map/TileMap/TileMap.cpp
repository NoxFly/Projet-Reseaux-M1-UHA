#include "TileMap.hpp"

#include <iostream>
#include <filesystem>

#include "utils.hpp"

namespace fs = std::filesystem;


TileMap::TileMap():
    m_tiles{},
    m_tileSize(0, 0)
{}

TileMap::~TileMap() {
    
}



bool TileMap::load(const std::string& tilepath, const std::string& prefix, const std::string& ext, uint width, uint height) {
    m_boardSize.x = width;
    m_boardSize.y = height;

    const uint tileCount = m_boardSize.x * m_boardSize.y;

    // put the correct total amount of tiles
    // all tiles are by default set to hasLoaded = false
    m_tiles.resize(tileCount);

    //
    uint i = 0;

    std::cout << i << "/" << tileCount << std::flush;
    //

    for(const auto &entry : fs::directory_iterator(tilepath)) {
        // get the index of the tile on the board
        const std::string prefixToRemove = tilepath + "/" + prefix + "_";
        const auto texId = replace(replace(entry.path(), prefixToRemove, ""), ext, "");
        const auto colrow = splitString(texId, "-");

        const uint col = std::stoi(colrow[1]);
        const uint row = (int)colrow[0][0] - 65;
        const uint index = width * row + col;

        // don't allow out of range of defined area (width, height)
        if(row > m_boardSize.y || col > m_boardSize.x) {
            continue;
        }

        // try to load the texture (image)
        if(!m_tiles[index].tex.loadFromFile(entry.path()))
            return false;

        m_tiles[index].tex.setSmooth(true);

        // if first image to load, then update the tile size (which is normally the same for every tile)
        sf::Vector2u size = m_tiles[index].tex.getSize();

        if(!m_tileSize.x) {
            m_tileSize = size;
        }
        // wrong size compared to what has been saved previously
        else if(size.x != m_tileSize.x || size.y != m_tileSize.y) {
            m_tiles[index].tex = sf::Texture(); // reset
        }

        // update the tile
        m_tiles[index].tile.setTexture(m_tiles[index].tex);
        m_tiles[index].tile.setPosition(m_tileSize.x * col, m_tileSize.y * row);
        m_tiles[index].position.x = col;
        m_tiles[index].position.y = row;
        // update state
        m_tiles[index].hasLoaded = true;


        // update console's loading index
        int l = std::to_string(i).size() + std::to_string(tileCount).size() + 1;

        for(int j=0; j < l; j++)
            std::cout << "\b";

        std::cout << ++i << "/" << tileCount << std::flush;
    }

    //
    int l = std::to_string(i).size() + std::to_string(tileCount).size() + 1;

    for(int j=0; j < l; j++)
        std::cout << "\b";

    std::cout << std::flush;
    //

    return true;
}

const Tile& TileMap::operator[](uint i) const {
    return m_tiles[i];
}

const Tile& TileMap::getTile(uint x, uint y) const {
    return m_tiles[m_boardSize.x * y + x];
}

const std::vector<Tile>& TileMap::getTiles() const {
    return m_tiles;
}

uint TileMap::tileCount() const {
    return m_tiles.size();
}

const sf::Vector2u& TileMap::getBoardDimension() const {
    return m_boardSize;
}

sf::Vector2u TileMap::getDimension() {
    sf::Vector2u v;

    v.x = m_boardSize.x * m_tileSize.x;
    v.y = m_boardSize.y * m_tileSize.y;

    return v;
}

const sf::Vector2u& TileMap::getTileSize() const {
    return m_tileSize;
}