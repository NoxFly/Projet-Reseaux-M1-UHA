#include "GeoPosition.hpp"
#include "math.h"

// static

void GeoPosition::defineMapLBT(const sf::Vector2f& top, const sf::Vector2f& bottom, const sf::Vector2u& size) {
    TOP_LEFT_LBT93 = top;
    BOT_RIGHT_LBT93 = bottom;
    MAP_SIZE_PX = size;

    MAP_SIZE_LBT93 = sf::Vector2f(
        abs(BOT_RIGHT_LBT93.x - TOP_LEFT_LBT93.x),
        abs(BOT_RIGHT_LBT93.y - TOP_LEFT_LBT93.y)
    );
}

sf::Vector2f GeoPosition::L2C(const sf::Vector2f& p) {
    return sf::Vector2f(
        (BOT_RIGHT_LBT93.x - p.x) / MAP_SIZE_LBT93.x * MAP_SIZE_PX.x,
        (BOT_RIGHT_LBT93.y - p.y) / MAP_SIZE_LBT93.y * MAP_SIZE_PX.y
    );
}

sf::Vector2f GeoPosition::C2L(const sf::Vector2f& p) {
    return sf::Vector2f(
        BOT_RIGHT_LBT93.x - (p.x * BOT_RIGHT_LBT93.x / MAP_SIZE_PX.x),
        BOT_RIGHT_LBT93.y + (p.y * BOT_RIGHT_LBT93.y / MAP_SIZE_PX.y)
    );
}


//

GeoPosition::GeoPosition(const sf::Vector2f& lambert):
    m_lambert{lambert},
    m_coords{}
{
    m_coords = L2C(m_lambert);
}
        
GeoPosition::~GeoPosition() {

}
        
const sf::Vector2f& GeoPosition::lambert() const {
    return m_lambert;
}

const sf::Vector2f& GeoPosition::coords() const {
    return m_coords;
}

void GeoPosition::setLambert(const sf::Vector2f& lambert) {
    m_lambert = lambert;
    m_coords = L2C(m_lambert);
}

void GeoPosition::setCoords(const sf::Vector2f& coords) {
    m_coords = coords;
    m_lambert = C2L(m_coords);
}