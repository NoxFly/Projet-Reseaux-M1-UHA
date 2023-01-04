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
        ~TileMap();

        TileMap& operator=(const TileMap& copy) = delete;

        /**
         * Load all the tiles from a given zoom level (in a dedicated folder).
         * If :
         *   - There's more images than expected,
         *   - The image's name is not correct,
         *   - The image's dimension is not the same than the 1st loaded,
         * => avoid it, don't save it.
         * All tiles default state is hasLoaded = false, which results in a blank square from renderer side.
         */
        bool load(const std::string& tilepath, const std::string& prefix, const std::string& ext, const unsigned int width, const unsigned int height);

        /**
         * Get a tile at a specific index in the 1D array (array size = width * height).
         */
        const Tile& operator[](const unsigned int i) const;
        /**
         * Get a tile at a specific index in the 2D array.
         */
        const Tile& getTile(const unsigned int x, const unsigned int y) const;
        /**
         * Returns all the tiles of this level.
         */
        const std::vector<Tile>& getTiles() const;
        /**
         * Returns the total number of tiles on this level (= width * height)
         */
        unsigned int tileCount() const;
        /**
         * Returns the size of the tiles of this level (each tiles have the same size).
         */
        const sf::Vector2u& getTileSize() const;
        /**
         * Returns the total dimension of this map (width * tileSize.x, height * tileSize.y).
         */
        sf::Vector2u getDimension() const;
        /**
         * Returns the number of tiles on both x/y axis on the board of this level.
         */
        const sf::Vector2u& getBoardDimension() const;

    protected:
        std::vector<Tile> m_tiles; // a 1D array storing all tiles of this level of zoom
        sf::Vector2u m_tileSize; // the common size of each tiles (they normally have all the same size)
        sf::Vector2u m_boardSize; // the number of tiles in the board, on both x/y axis
};

#endif // TILEMAP_HPP