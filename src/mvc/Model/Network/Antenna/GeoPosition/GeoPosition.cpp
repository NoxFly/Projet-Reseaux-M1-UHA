#include "GeoPosition.hpp"

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

}
        
void GeoPosition::C2L() {
    
}