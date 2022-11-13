#include "GeoPosition.hpp"
#include "math.h"

GeoPosition::GeoPosition(sf::Vector2<float> lambert) : m_lambert{lambert}, m_coords{} {
    L2C();
}
        
GeoPosition::~GeoPosition() {

}
        
sf::Vector2<float> GeoPosition::lambert() const {
    return m_lambert;
}

sf::Vector2<float> GeoPosition::coords() const {
    return m_coords;
}

void GeoPosition::setLambert(const sf::Vector2<float>& lambert) {
    m_lambert = lambert;
    L2C();
}

void GeoPosition::setCoords(const sf::Vector2<float>& coords) {
    m_coords = coords;
    C2L();
}
        
void GeoPosition::L2C() {
    float refX = abs(1037842.881126 - 1012539.918657);
    float refY = abs(6737765.159074 - 6760952.253250);
    m_coords.x = abs(m_lambert.x - 1037842.881126) * 3828 / refX;
    m_coords.y = abs(m_lambert.y - 6737765.159074) * 3828 / refY;
}
        
void GeoPosition::C2L() {
    m_lambert.x = 1037842.881126 - (m_coords.x * 1037842.881126 / 3828);
    m_lambert.y = 6737765.159074 + (m_coords.y * 6737765.159074 / 3828);
}