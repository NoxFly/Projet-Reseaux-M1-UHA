#include "Antenna.hpp"

#ifdef DEBUG
#include <iostream>
#endif

#include <string>
#include <SFML/System/Vector2.hpp>

#include "utils/utils.hpp"

Antenna::Antenna(const sf::Vector2f& position, const float range, const unsigned int freq, const int alt):
    Colorable(),
    m_position(position),
    m_range{range},
    m_frequency{freq},
    m_altitude{alt},
    m_name("name-not-defined"),
    m_uuid(uuid::generate_uuid_v4())
{
#ifdef DEBUG
    int x = m_position.coords().x;
    int xl = std::to_string(x).size();
    int y = m_position.coords().y;
    int yl = std::to_string(y).size();

    int l = 6;

    std::cout << "New antenna "
        << "(" << x << ", ";

    for(int i=0; i < (l-xl); i++)
        std::cout << " ";
        
    std::cout << y << ")";

    for(int i=0; i < (l-yl); i++)
        std::cout << " ";

    std::cout
        << "[" << std::fixed << m_position.lambert().x << ", " << m_position.lambert().y  << std::defaultfloat <<"]"
        << std::endl;

#endif
}

Antenna::~Antenna() {

}

const GeoPosition& Antenna::getPosition() const {
    return m_position;
}

float Antenna::getRange() const {
    return m_range;
}

unsigned int Antenna::getFreq() const {
    return m_frequency;
}

int Antenna::getAltitude() const {
    return m_altitude;
}

const std::string& Antenna::getName() const {
    return m_name;
}

const char * Antenna::getUUID() {
    return m_uuid;
}

void Antenna::setFreq(const int freq) {
    m_frequency = freq;
}

void Antenna::setAltitude(const int alt) {
    m_altitude = alt;
}

void Antenna::setRange(const float range) {
    m_range = range;
}