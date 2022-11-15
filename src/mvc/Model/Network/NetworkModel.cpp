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

void NetworkModel::loadFromConfig(const AppConfig& config) {
	//extract path from config
	std::ifstream file(config.network.entryFile);
	//default delimter
	std::string delimeter = " ";

	if (file.is_open()) {//only read if file is not empty

		std::string line;//hold current line

		while (std::getline(file, line)) {
			
			//init vector
			std::vector<double> antennaValues;

			//@see https://java2blog.com/split-string-space-cpp/#:~:text=You%20can%20use%20string's%20find,be%20used%20for%20any%20delimeter.
			int start = 0;
			int end = line.find(delimeter);

			while (end != -1) {
				//push sample value
				antennaValues.push_back(
										std::stod(
											line.substr(start, end - start)
											)
										);

				start = end + delimeter.size();
				end = line.find(delimeter, start);
			}

			//push sample value
			antennaValues.push_back(
									std::stod(
										line.substr(start, end - start)
										)
									);

			if(antennaValues.size() == 3) {
				//declare antenna
				sf::Vector2<double> pos(antennaValues.at(0), antennaValues.at(1));
				//frequency and altitude are hardcoded in this example
				Antenna newantenna(pos, antennaValues.at(2), 4, 4);

				m_network.push_back(newantenna);
			}

			printf("\n");

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