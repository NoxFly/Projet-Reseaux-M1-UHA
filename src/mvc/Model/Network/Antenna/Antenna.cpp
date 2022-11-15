#include "Antenna.hpp"
#include "utils.hpp"
#include <string>
#include <SFML/System/Vector2.hpp>

GeoPosition Antenna::getPosition() const {
    return m_position;
}

Antenna::Antenna(sf::Vector2f position,const float range,const int freq,const int alt):
    m_position(position),
    m_range{range},
    m_frequency{freq},
    m_altitude{alt},
    m_uuid(uuid::generate_uuid_v4())
{

}

Antenna::~Antenna() {

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

std::string Antenna::getName() const {
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
