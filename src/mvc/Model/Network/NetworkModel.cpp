#include "NetworkModel.hpp"
#include "Antenna.hpp"
#include <iostream>
#include <string.h>
#include <fstream>
#include <SFML/System/Vector2.hpp>


NetworkModel::NetworkModel() {

}

NetworkModel::~NetworkModel() {

}

void NetworkModel::loadFromConfig(const NetworkConfig& config) {
	// extract path from config
	std::ifstream file(config.entryFile);
	// default delimter

	if(file.is_open()) { // only read if file is not empty

		std::string line; // hold current line

		while(std::getline(file, line)) {
            // a line is modelised here as "0.0 0.0 0.0" (3 floats)
            // and in order "X Y RANGE" and where X,Y are in lambert
            float x, y, r;

            sscanf(line.c_str(), "%f %f %f", &x, &y, &r);

            // at least one the 3 floats does not respect the float form
            if(x < .1 || y < .1 || r < .1) {
                continue;
            }

            Antenna newantenna(sf::Vector2f(x, y), r, 4, 4);

            m_network.push_back(newantenna);
		}

		file.close();
	}
	
}

const std::vector<Antenna>& NetworkModel::getNetwork() const {
	return m_network;
}

Antenna NetworkModel::getNetworkAt(unsigned int i) {
    return m_network[i];
}

void NetworkModel::setNetwork(const std::vector<Antenna>& network) {
    m_network = network;
}