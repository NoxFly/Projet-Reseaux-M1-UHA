#include "Antenna.hpp"

Antenna::Antenna(const int x, const int y, const int distance):
    m_x{x}, m_y{y}, m_distance{distance}
{

}

Antenna::~Antenna() {

}

int Antenna::getX() const {
    return m_x;
}

int Antenna::getY() const {
    return m_y;
}

int Antenna::getRange() const {
    return m_distance;
}

void Antenna::setX(const int x) {
    m_x = x;
}

void Antenna::setY(const int y) {
    m_y = y;
}

void Antenna::setRange(const int distance) {
    m_distance = distance;
}

double Antenna::Intensity() { // Calculer l'intensité d'une antenne (regarde cours mais pas sûr du vocabulaire employé)
    return 0.f;
}