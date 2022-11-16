#ifndef GEOPOSITION_HPP
#define GEOPOSITION_HPP

#include <SFML/System/Vector2.hpp>


class GeoPosition {
    public:
        static void defineMapLBT(const sf::Vector2f& top, const sf::Vector2f& bottom, const sf::Vector2u& size);

        GeoPosition(const sf::Vector2f& lambert);
        ~GeoPosition();

        // send a constant reference (just to read the value)
        const sf::Vector2f& lambert() const;
        const sf::Vector2f& coords() const;

        void setLambert(const sf::Vector2f& lambert);
        void setCoords(const sf::Vector2f& coords);

    private:
        // lambert93 coords
        // static configuration changed by the map
        static inline sf::Vector2f TOP_LEFT_LBT93 = sf::Vector2f(0, 0);
        static inline sf::Vector2f BOT_RIGHT_LBT93 = sf::Vector2f(0, 0);
        static inline sf::Vector2u MAP_SIZE_PX = sf::Vector2u(0, 0);
        static inline sf::Vector2f MAP_SIZE_LBT93 = sf::Vector2f(0, 0);

        static sf::Vector2f L2C(const sf::Vector2f& p);
        static sf::Vector2f C2L(const sf::Vector2f& p);

        sf::Vector2f m_lambert;
        sf::Vector2f m_coords;
};


#endif //GEOPOSITION_HPP