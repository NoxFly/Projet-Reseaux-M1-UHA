#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <vector>

#include "Antenna.hpp"
#include "config_interfaces.hpp"

class NetworkModel {
	public:
		NetworkModel();
		~NetworkModel();

		void loadFromConfig(const NetworkConfig& config);

		Antenna getNetworkAt(unsigned int i);
        const std::vector<Antenna>& getNetwork() const;

        void setNetwork(const std::vector<Antenna>& network);

	private:
        std::vector<Antenna> m_network;
};

#endif // NETWORK_HPP