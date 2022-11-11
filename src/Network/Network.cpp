#include "Network.hpp"

#include <vector>

Network::Network() : d_network{} {

}

Network::Network(std::vector<Antenne> network) : d_network {network} {

}

Network::~Network() {

}


Antenne Network::getNetworkAt(int i) {
    return d_network[i];
}

//void setNetworkAt(Antenne antenne, int i)

void Network::setNetwork(std::vector<Antenne> network) {
    d_network = network;
}