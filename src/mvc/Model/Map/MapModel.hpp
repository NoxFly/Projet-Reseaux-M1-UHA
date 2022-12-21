#ifndef MAP_HPP
#define MAP_HPP

#include <map>
#include <memory>
#include <SFML/Graphics.hpp>

#include "config_interfaces.hpp"
#include "TileMap/TileMap.hpp"

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
        const TileMap& getTilesOfLevel(const unsigned int level) const;

        /**
         * Returns the TileMap object of the requested level of zoom.
         * Can throw an error if the requested level does not exists (is out of bounds).
         */
        TileMap& getTilesOfLevel(const unsigned int level);

        /**
         * Returns the number of zoom levels it can handles.
         * Basically, if there's 3 levels of zoom, it returns 3,
         * which is also the index for the last level of zoom (which zooms the most).
         * You can then use it for example like this :
         * @example
         * map.getMapDimension(map.getZoomLevels())
         */
        unsigned int getZoomLevels();

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
        sf::Vector2u getMapDimension(const unsigned int level);

        /**
         * Returns the tiles of the current level.
         */
        const std::vector<Tile>& getTiles() const;

        /**
         * Returns the dimension of the tiles of the current level.
         */
        const sf::Vector2u& getTileSize() const;

        
        float getCurrentRatio() const;
        

        /**
         * Returns the current zoom's level.
         */
        unsigned int getZoomLevel() const;

        /**
         * Change the zoom's level.
         * If the requested level does not exist, does nothing.
         */
        void setZoomLevel(const unsigned int level);

        /**
         * Returns the position of the "camera", the translation of the map.
         */
        sf::Vector2i getPosition() const;

        /**
         * Defines the new position of the map in the view.
         */
        void setPosition(const sf::Vector2i& position);

        /**
         * Defines the new position of the map in the view.
         */
        void setPosition(const unsigned int x, const unsigned int y);
        
        /**
         * Moves the map relativly with this vector.
         */
        void move(const sf::Vector2i& position);

        /**
         * Moves the map relativly with this vector.
         */
        void move(const unsigned int x, const unsigned int y);

        /**
         * Zoom in to the next level of zoom, z+1, > 0, <= m_config.zoomLevels.
         */
        void zoomIn();

        /**
         * Zoom out to the previous level of zoom, z-1, > 0, <= m_config.zoomLevels.
         */
        void zoomOut();

        void grab(const sf::Vector2i& mouse);
        void ungrab();
        void grabMove(const sf::Vector2i& mouse);

    protected:
        void centerPosition();
        void clampPosition();
        void clampPosition(const sf::Vector2i& mouse);

        MapConfig m_config;
        std::vector<TileMap> m_tiles; // size = n
        std::vector<float> m_zoomRatio; // size = n-1 : compares the ratio between max zoom and others
        // for a level of zoom of 3 :
        // tiles: { zoom1, zoom2, zoom3 }
        // ratio: { ratio3x1, ratio3x2 }
        unsigned int m_currentZoomLevel; // starts from 1, between 1 and maxZoomLevel
        
        bool m_grabbing;
        sf::Vector2i m_oldPosition;
        sf::Vector2i m_grabPoint;
        sf::Vector2i m_position; // translation position of the center of the window targeting the map.
};

#endif // MAP_HPP