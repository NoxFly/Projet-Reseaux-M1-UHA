#ifndef GEOPOSITION_HPP
#define GEOPOSITION_HPP

#include <SFML/System/Vector2.hpp>

class GeoPosition {
    public :
        GeoPosition(sf::Vector2<float> lambert);
        ~GeoPosition();
        sf::Vector2<float> lambert() const;
        sf::Vector2<float> coords() const;
        void setLambert(const sf::Vector2<float>& lambert);
        void setCoords(const sf::Vector2<float>& coords);
        void L2C();
        void C2L();
    private :
        sf::Vector2<float> m_lambert;
        sf::Vector2<float> m_coords;
};


#endif //GEOPOSITION_HPP