#ifndef ANTENNA_HPP
#define ANTENNA_HPP

#include "GeoPosition.hpp"
#include <string>
#include <SFML/System/Vector2.hpp>

class Antenna {
    public :
        
        GeoPosition getPosition() const;

        Antenna(
            sf::Vector2f position,
            const float range,
            const int freq,
            const int alt
        );
        ~Antenna();

        float getRange() const;
        int getFreq() const;
        int getAltitude() const;
        std::string getName() const;
        const char * getUUID();

        void setFreq(const int);
        void setAltitude(const int);
        void setRange(const float);

    private :
        GeoPosition m_position;
        float m_range;
        int m_frequency;
        int m_altitude;
        std::string m_name;
        const char * m_uuid;
};

#endif // ANTENNA_HPP