#include "NetworkModel.hpp"

NetworkModel::NetworkModel() {

}

NetworkModel::~NetworkModel() {

}

void NetworkModel::loadFromConfig(const AppConfig& config) {
	// TODO : config.network
	(void)config;
}

Antenna NetworkModel::getNetworkAt(unsigned int i) {
	return m_network.at(i);
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