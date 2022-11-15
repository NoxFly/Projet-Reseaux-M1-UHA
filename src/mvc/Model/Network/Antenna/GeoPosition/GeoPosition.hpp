#ifndef GEOPOSITION_HPP
#define GEOPOSITION_HPP

#include <SFML/System/Vector2.hpp>

class GeoPosition {
    public :
        GeoPosition(sf::Vector2<double> lambert);
        ~GeoPosition();
        //replace returned type to Lambert struct
        sf::Vector2<double> lambert() const;
        sf::Vector2<double> coords() const;
        void setLambert(const sf::Vector2<double>& lambert);
        void setCoords(const sf::Vector2<double>& coords);
        void L2C();
        void C2L();
    private :
        sf::Vector2<double> m_lambert;
        sf::Vector2<double> m_coords;
};


#endif //GEOPOSITION_HPP