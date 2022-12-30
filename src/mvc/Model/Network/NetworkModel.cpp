#include "NetworkModel.hpp"

#include <iostream>
#include <string.h>
#include <fstream>

#include <SFML/System/Vector2.hpp>


NetworkModel::NetworkModel():
    m_network{},
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

		while(std::getline(file, line)) {
            // a line is modelised here as "0.0 0.0 0.0" (3 floats)
            // and in order "X Y RANGE" and where X,Y are in lambert
            std::string name;
            char cname[] = "unamed XXX-XXX-XXX-XXX";
            float x, y, r;

            sscanf(line.c_str(), "%s %f %f %f", cname, &x, &y, &r);

            // at least one of the 3 floats does not respect the float form
            if(x < .1 || y < .1 || r < .1) {
                // continue;
            }

            name = std::string(cname);

            if(name.size() == 0) {
                name = "unamed";
            }

            Antenna antenna(name, sf::Vector2f(x, y), r, 0, 0);

            m_network.push_back(antenna);
		}

		file.close();

#ifdef DEBUG
        std::cout << std::endl;
#endif
	}
	else {
        throw std::runtime_error("[ERROR] NetworkModel::loadFromConfig : Failed to open the sample file.");
    }
}

const std::vector<Antenna>& NetworkModel::getAntennas() const {
	return m_network;
}

std::vector<Antenna>& NetworkModel::getAntennas() {
	return m_network;
}

Antenna& NetworkModel::getNetworkAt(const unsigned int i) {
    return m_network[i];
}

const Antenna& NetworkModel::getNetworkAt(const unsigned int i) const {
    return m_network[i];
}

void NetworkModel::clear() {
    m_network.clear();
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
