#ifndef ANTENNA_HPP
#define ANTENNA_HPP

#include <string>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

#include "GeoPosition.hpp"


class Antenna {
    public :
        Antenna(
            const sf::Vector2f& position,
            const float range,
            const int freq,
            const int alt
        );
        ~Antenna();

        const GeoPosition& getPosition() const;
        float getRange() const;
        int getFreq() const;
        int getAltitude() const;
        const std::string& getName() const;
        const char * getUUID();

        void setFreq(const int);
        void setAltitude(const int);
        void setRange(const float);

        // view modifiers
        void setColor(const sf::Color& color);
        const sf::Color& getColor() const;

    private :
        GeoPosition m_position;
        float m_range;
        int m_frequency;
        int m_altitude;
        sf::Color m_color;
        std::string m_name;
        const char * m_uuid;
};

#endif // ANTENNA_HPP