#ifndef GEOPOSITION_HPP
#define GEOPOSITION_HPP

#include <SFML/System/Vector2.hpp>


class GeoPosition {
    public:
        static void defineMapLBT(
            const sf::Vector2i& top,
            const sf::Vector2i& bottom,
            const sf::Vector2u& sizePX,
            const sf::Vector2u& sizeMTR
        );

        GeoPosition(const sf::Vector2i& lambert);
        ~GeoPosition();

        // send a constant reference (just to read the value)
        const sf::Vector2i& lambert() const;
        const sf::Vector2i& pixels() const;
        const sf::Vector2i& meters() const;

        void setLambert(const sf::Vector2i& lambert);
        void setPixels(const sf::Vector2i& coords);

    private:
        // lambert93 coords
        // static configuration changed by the map
        static inline sf::Vector2i TOP_LEFT_LBT93 = sf::Vector2i(0, 0);
        static inline sf::Vector2i BOT_RIGHT_LBT93 = sf::Vector2i(0, 0);
        static inline sf::Vector2u MAP_SIZE_PX = sf::Vector2u(0, 0);
        static inline sf::Vector2u MAP_SIZE_MTR = sf::Vector2u(0, 0);
        static inline sf::Vector2i MAP_SIZE_LBT93 = sf::Vector2i(0, 0);

        static sf::Vector2i L2C(const sf::Vector2i& p);
        static sf::Vector2i C2L(const sf::Vector2i& p);

        sf::Vector2i m_lambert;
        sf::Vector2i m_coordsPixels;
        sf::Vector2i m_coordsMeters;
};


#endif //GEOPOSITION_HPP