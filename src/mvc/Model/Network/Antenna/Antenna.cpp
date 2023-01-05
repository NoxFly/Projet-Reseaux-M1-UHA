#include "Antenna.hpp"

#ifdef DEBUG
#include <iostream>
#endif

#include <string>
#include <SFML/System/Vector2.hpp>

#include "utils/utils.hpp"

Antenna::Antenna():
    Antenna("unamed", sf::Vector2i(0, 0), 0, 0, 0)
{}

Antenna::Antenna(const std::string& name, const sf::Vector2i& position, const unsigned int range, const unsigned int freq, const int alt):
    Colorable(),
    m_position(position),
    m_power(0),
    m_range(range),
    m_frequency(freq),
    m_altitude(alt),
    m_name(name),
    m_uuid(uuid::generate_uuid_v4())
{
#ifdef DEBUG
    int x = m_position.pixels().x;
    int xl = std::to_string(x).size();
    int y = m_position.pixels().y;
    int yl = std::to_string(y).size();

    int l = 6;

    std::cout << "New antenna "
        << "(" << x << ", ";

    std::cout << repeat(' ', l-xl);
        
    std::cout << y << ")";

    std::cout << repeat(' ', l-yl);

    std::cout
        << "[" << m_position.lambert().x << ", " << m_position.lambert().y <<"]";

    std::cout
        << " #" << m_uuid << " '" << m_name << "'"
        << std::endl;

#endif
}

Antenna::~Antenna() {

}

const GeoPosition& Antenna::getPosition() const {
    return m_position;
}

float Antenna::getEmitPower() const {
    return m_power;
}

unsigned int Antenna::getRange() const {
    // TODO : calculate depending of power (PATHLOSS ?)
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

const std::string Antenna::getUUID() const {
    return m_uuid;
}

void Antenna::setFreq(const int freq) {
    m_frequency = freq;
}

void Antenna::setAltitude(const int alt) {
    m_altitude = alt;
}

void Antenna::setRange(const unsigned int range) {
    m_range = range;
}