#ifndef ANTENNA_HPP
#define ANTENNA_HPP

#include "GeoPosition.hpp"
#include <string>
#include <SFML/System/Vector2.hpp>

class Antenna {
    public :
        
        GeoPosition getPosition() const;

        Antenna(
            sf::Vector2<float> position,
            const float range,
            const int freq,
            const int alt
        );
        ~Antenna();

        float getRange() const;
        int getFreq() const;
        int getAltitude() const;
        std::string getName() const;
        auto getUUID() const;

        void setFreq(const int);
        void setAltitude(const int);
        void setRange(const float);

    private :
        GeoPosition m_position;
        float m_range;
        int m_frequency;
        int m_altitude;
        std::string m_name;
        char m_uuid[36];
};

#endif // ANTENNA_HPP