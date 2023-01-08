#ifndef ANTENNA_HPP
#define ANTENNA_HPP

#include <string>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

#include "GeoPosition/GeoPosition.hpp"
#include "mvc/Model/Network/Graphe/Colorable/Colorable.hpp"


class Antenna: public Colorable {
    public:
        Antenna();
        Antenna(
            const std::string& name,
            const sf::Vector2i& position,
            const unsigned int range,
            const unsigned int freq,
            const int alt
        );
        ~Antenna();

        const GeoPosition& getPosition() const;
        float getEmitPower() const;
        unsigned int getRange() const;
        unsigned int getFreq() const;
        int getAltitude() const;
        const std::string& getName() const;
        const std::string& getUUID() const;

        void setFreq(const int);
        void setAltitude(const int);
        void setRange(const unsigned int);

    private:
        GeoPosition m_position;
        float m_power;
        unsigned int m_range;
        unsigned int m_frequency;
        int m_altitude;
        std::string m_name;
        const std::string m_uuid;
};

#endif // ANTENNA_HPP