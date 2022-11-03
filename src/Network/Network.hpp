#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <vector>
#include "Antenne.hpp"

class Network {
    public :
        Network();
        Network(std::vector<Antenne> network);
        ~Network();
        Antenne getNetworkAt(int i);
        Antenne getNetwork();
        //void setNetworkAt(Antenne antenne, int i);
        void setNetwork(std::vector<Antenne> network);
    private :
        std::vector<Antenne> d_network;
};

#endif