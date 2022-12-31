#include "NetworkModel.hpp"

#include <iostream>
#include <string.h>
#include <fstream>

#include <SFML/System/Vector2.hpp>

#include "mvc/Model/Network/Graphe/Graphe.hpp"
#include "utils/utils.hpp"


NetworkModel::NetworkModel():
    m_antennas{},
    m_showAntennas(true),
    m_showRanges(false),
    m_showColors(false)
{

}

NetworkModel::~NetworkModel() {

}

void NetworkModel::loadFromConfig(const NetworkConfig& config) {
	std::ifstream file(config.entryFile);
    std::string line;


	if(file.is_open()) { // only read if file exists and is not empty

        m_antennas.clear();

		while(std::getline(file, line)) {
            // a line is modelised here as "0.0 0.0 0.0" (3 floats)
            // and in order "X Y RANGE" and where X,Y are in lambert
            float x, y, r;

            sscanf(line.c_str(), "%f %f %f", &x, &y, &r);

            // at least one of the 3 floats does not respect the float form
            if(x < .1 || y < .1 || r < .1) {
                // continue;
            }

            auto ant = std::make_unique<Antenna>(sf::Vector2f(x, y), r, 4, 4);

            m_antennas.push_back(std::move(ant));
		}

		file.close();

#ifdef DEBUG
        std::cout << std::endl;
#endif

	}
	else {
        throw std::runtime_error("[ERROR] NetworkModel::loadFromConfig : Failed to open the sample file.");
    }




    // ------ GRAPH / COLORIZATION ------
    updateColorization();
}

void NetworkModel::updateColorization() {
    //do logic to figure out which antennas are in each others zone
    // for every two interfering antennas, take their indexes
    // and pass them to addEdge method of Graphe class
    unsigned int antennasCr = m_antennas.size();

	Graphe graphe(antennasCr);

    // 1st. Add vertices
    for(unsigned int i=0; i < antennasCr; i++) {
        graphe.addVertex(i, (*this)[i]);
    }

    // 2nd. Add edges
    for(unsigned int i=0; i < antennasCr; i++) {
        for(unsigned int j=i+1; j < antennasCr; j++) {
            // Antennas
            auto a = (*this)[i];
            auto b = (*this)[j];

            const unsigned int rangesCollide = circleToCircleCollision(
                a->getPosition().lambert().x,
                a->getPosition().lambert().y,
                a->getRange(),
                b->getPosition().lambert().x,
                b->getPosition().lambert().y,
                b->getRange()
            );

            if(rangesCollide != 0) {
                graphe.addEdge(i, j);
            }
        }
    }

	graphe.colorize();
}

const std::vector<std::unique_ptr<Antenna>>& NetworkModel::getAntennas() const {
	return m_antennas;
}

Antenna* NetworkModel::getAntennaByIndex(const unsigned int i) {
    return m_antennas[i].get();
}

Antenna* NetworkModel::operator[](const unsigned int i) {
    return m_antennas[i].get();
}

void NetworkModel::showAntennas(const bool state) {
    m_showAntennas = state;
}

void NetworkModel::showRanges(const bool state) {
    m_showRanges = state;
}

void NetworkModel::showColors(const bool state) {
    m_showColors = state;
}

bool NetworkModel::shouldShowAntennas() const {
    return m_showAntennas;
}

bool NetworkModel::shouldShowRanges() const {
    return m_showRanges;
}

bool NetworkModel::shouldShowColors() const {
    return m_showColors;
}
