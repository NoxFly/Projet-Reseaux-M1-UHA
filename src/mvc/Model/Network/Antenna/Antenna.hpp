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
            const sf::Vector2f& position,
            const float range,
            const unsigned int freq,
            const int alt
        );
        ~Antenna();

        const GeoPosition& getPosition() const;
        float getEmitPower() const;
        float getRange() const;
        unsigned int getFreq() const;
        int getAltitude() const;
        const std::string& getName() const;
        const std::string getUUID() const;

        void setFreq(const int);
        void setAltitude(const int);
        void setRange(const float);

    private:
        GeoPosition m_position;
        float m_power;
        float m_range;
        unsigned int m_frequency;
        int m_altitude;
        std::string m_name;
        const std::string m_uuid;
};

#endif // ANTENNA_HPP