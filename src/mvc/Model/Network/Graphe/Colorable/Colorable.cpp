#include "Colorable.hpp"

Colorable::Colorable():
    m_color(sf::Color::Black)
{

}

Colorable::~Colorable() {

}

const sf::Color& Colorable::getColor() const {
    return m_color;
}

void Colorable::setColor(const sf::Color& color) {
    m_color = color;
}