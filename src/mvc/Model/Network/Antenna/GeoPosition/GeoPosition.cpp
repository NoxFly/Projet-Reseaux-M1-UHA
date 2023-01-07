#include "GeoPosition.hpp"
#include "math.h"

#include <iostream>

// static

void GeoPosition::defineMapLBT(const sf::Vector2i& top, const sf::Vector2i& bottom, const sf::Vector2u& sizePX, const sf::Vector2u& sizeMTR) {
    TOP_LEFT_LBT93 = top;
    BOT_RIGHT_LBT93 = bottom;
    MAP_SIZE_PX = sizePX;
    MAP_SIZE_MTR = sizeMTR;

    MAP_SIZE_LBT93 = sf::Vector2i(
        abs(BOT_RIGHT_LBT93.x - TOP_LEFT_LBT93.x),
        abs(BOT_RIGHT_LBT93.y - TOP_LEFT_LBT93.y)
    );
}

sf::Vector2i GeoPosition::L2C(const sf::Vector2i& p) {
    return sf::Vector2i(
        abs(p.x - TOP_LEFT_LBT93.x) * MAP_SIZE_PX.x / MAP_SIZE_LBT93.x,
        abs(p.y - TOP_LEFT_LBT93.y) * MAP_SIZE_PX.y / MAP_SIZE_LBT93.y
    );
}

sf::Vector2i GeoPosition::C2L(const sf::Vector2i& p) {
    auto l = sf::Vector2i(
        TOP_LEFT_LBT93.x + (p.x * MAP_SIZE_LBT93.x / MAP_SIZE_PX.x),
        TOP_LEFT_LBT93.y - (p.y * MAP_SIZE_LBT93.y / MAP_SIZE_PX.y)
    );

    return l;
}


//

GeoPosition::GeoPosition(const sf::Vector2i& lambert):
    m_lambert{0, 0},
    m_coordsPixels{0, 0},
    m_coordsMeters{0, 0}
{
    setLambert(lambert);
}
        
GeoPosition::~GeoPosition() {

}
        
const sf::Vector2i& GeoPosition::lambert() const {
    return m_lambert;
}

const sf::Vector2i& GeoPosition::pixels() const {
    return m_coordsPixels;
}

const sf::Vector2i& GeoPosition::meters() const {
    return m_coordsMeters;
}

void GeoPosition::setLambert(const sf::Vector2i& lambert) {
    m_lambert = lambert;
    m_coordsPixels = L2C(m_lambert);

    m_coordsMeters.x = m_coordsPixels.x / (float)GeoPosition::MAP_SIZE_PX.x * GeoPosition::MAP_SIZE_MTR.x;
    m_coordsMeters.y = m_coordsPixels.y / (float)GeoPosition::MAP_SIZE_PX.y * GeoPosition::MAP_SIZE_MTR.y;
}

void GeoPosition::setPixels(const sf::Vector2i& coords) {
    m_coordsPixels = coords;
    m_lambert = C2L(m_coordsPixels);
}