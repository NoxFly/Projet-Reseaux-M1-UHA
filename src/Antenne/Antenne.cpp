#include "Antenne.hpp"

Antenne::Antenne(int x, int y, int distance) : d_x{x}, d_y{y}, d_distance{distance} {

}

Antenne::~Antenne() {

}

int Antenne::getX() {
    return d_x;
}

int Antenne::getY() {
    return d_y;
}

int Antenne::getDistance() {
    return d_distance;
}

void Antenne::setX(int x) {
    d_x = x;
}

void Antenne::setY(int y) {
    d_y = y;
}

void Antenne::setDistance(int distance) {
    d_distance = distance;
}

double Antenne::Intensite() { //Calculer l'intensité d'une antenne (regarde cours mais pas sûr du vocabulaire employé)

}