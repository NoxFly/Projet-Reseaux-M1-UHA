#ifndef MAP_HPP
#define MAP_HPP

#include <map>
#include <memory>
#include <SFML/Graphics.hpp>

#include "config_interfaces.hpp"
#include "TileMap.hpp"

class MapModel {
	public:
		MapModel();
		~MapModel();

        void loadFromConfig(const MapConfig& config);
        const TileMap& getTilesOfLevel(uint level) const;
        TileMap& getTilesOfLevel(uint level);

        uint getZoomLevels();
        sf::Vector2u getBoardDimension();

    protected:
        MapConfig m_config;
        std::vector<TileMap> m_tiles;
};

#endif // MAP_HPP