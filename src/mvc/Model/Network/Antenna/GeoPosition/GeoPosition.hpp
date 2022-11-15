#ifndef GEOPOSITION_HPP
#define GEOPOSITION_HPP

#include <SFML/System/Vector2.hpp>

class GeoPosition {
    public :
        GeoPosition(sf::Vector2f lambert);
        ~GeoPosition();

        sf::Vector2f lambert() const;
        sf::Vector2f coords() const;

        void setLambert(const sf::Vector2f& lambert);
        void setCoords(const sf::Vector2f& coords);

    private :
        void L2C();
        void C2L();
        sf::Vector2f m_lambert;
        sf::Vector2f m_coords;
};


#endif //GEOPOSITION_HPP