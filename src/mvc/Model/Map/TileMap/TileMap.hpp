#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>


struct Tile {
    sf::Texture tex;
    sf::Sprite tile;
    sf::Vector2u position;
    bool hasLoaded = false;
};


class TileMap {
    public:
        TileMap();
        // TileMap(const TileMap& copy) = delete;
        ~TileMap();

        TileMap& operator=(const TileMap& copy) = delete;

        bool load(const std::string& tilepath, const std::string& prefix, const std::string& ext, uint width, uint height);

        const Tile& operator[](uint i) const;

        const std::vector<Tile>& tiles() const;

        uint tileCount() const;
        const sf::Vector2u& getTileSize() const;
        sf::Vector2u getDimension();
        const sf::Vector2u& getBoardDimension() const;

    protected:
        std::vector<Tile> m_tiles;
        sf::Vector2u m_tileSize;
        sf::Vector2u m_boardSize;
};

#endif // TILEMAP_HPP