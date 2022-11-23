#include "Antenna.hpp"

#ifdef DEBUG
#include <iostream>
#endif

#include <string>
#include <SFML/System/Vector2.hpp>

#include "utils.hpp"

Antenna::Antenna(const sf::Vector2f& position, const float range, const int freq, const int alt):
    m_position(position),
    m_range{range},
    m_frequency{freq},
    m_altitude{alt},
    m_color(sf::Color::Black),
    m_name("name-not-defined"),
    m_uuid(uuid::generate_uuid_v4())
{
#ifdef DEBUG
    std::cout << "New antenna "
        << "(" << m_position.coords().x << ", " << m_position.coords().y << ")"
        << "[" << std::fixed << m_position.lambert().x << ", " << m_position.lambert().y <<"]"
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

int Antenna::getFreq() const {
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

void Antenna::setColor(const sf::Color& color) {
    m_color = color;
}

const sf::Color& Antenna::getColor() const {
    return m_color;
}
