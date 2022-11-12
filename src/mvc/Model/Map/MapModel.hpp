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

        /**
         * Loads all the maps from different levels with the given configuration.
         * It can throw an error if the number of levels is bigger than the folders.
         * It also setup the ratio between the last level of zoom (the biggest) and the others.
         */
        void loadFromConfig(const MapConfig& config);
        /**
         * Returns the TileMap object of the requested level of zoom.
         * Can throw an error if the requested level does not exists (is out of bounds).
         */
        const TileMap& getTilesOfLevel(uint level) const;
        /**
         * Returns the TileMap object of the requested level of zoom.
         * Can throw an error if the requested level does not exists (is out of bounds).
         */
        TileMap& getTilesOfLevel(uint level);
        /**
         * Returns the number of zoom levels it can handles.
         * Basically, if there's 3 levels of zoom, it returns 3,
         * which is also the index for the last level of zoom (which zooms the most).
         * You can then use it for example like this :
         * @example
         * map.getMapDimension(map.getZoomLevels())
         */
        uint getZoomLevels();
        /**
         * Returns the number of tiles on the map.
         * It is the same amount for each level.
         */
        sf::Vector2u getBoardDimension();
        /**
         * Returns the total dimension of the current map.
         */
        sf::Vector2u getMapDimension();
        /**
         * Returns the total dimension of the map of the requested level.
         * You can then use it for example like this :
         * @example
         * map.getMapDimension(map.getZoomLevels())
         */
        sf::Vector2u getMapDimension(uint level);
        /**
         * Returns the tiles of the current level.
         */
        const std::vector<Tile>& getTiles() const;

        /**
         * Returns the current zoom's level.
         */
        uint getZoomLevel() const;
        /**
         * Change the zoom's level.
         * If the requested level does not exist, does nothing.
         */
        void setZoomLevel(uint level);

        /**
         * Returns the position of the "camera", the translation of the map.
         */
        sf::Vector2f getPosition() const;

    protected:
        void centerPosition();

        MapConfig m_config;
        std::vector<TileMap> m_tiles; // size = n
        std::vector<float> m_zoomRatio; // size = n-1 : compares the ratio between max zoom and others
        // for a level of zoom of 3 :
        // tiles: { zoom1, zoom2, zoom3 }
        // ratio: { ratio3x1, ratio3x2 }
        uint m_currentZoomLevel; // starts from 1, between 1 and maxZoomLevel
        
        sf::Vector2f m_position; // translation position of the center of the window targeting the map.
};

#endif // MAP_HPP