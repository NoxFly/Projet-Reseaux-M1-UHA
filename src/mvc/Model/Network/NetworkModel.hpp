#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <vector>

#include "Antenna/Antenna.hpp"
#include "config_interfaces.hpp"

class NetworkModel {
	public:
		NetworkModel();
		~NetworkModel();

		void loadFromConfig(const NetworkConfig& config);

		Antenna& getNetworkAt(const unsigned int i);
		const Antenna& getNetworkAt(const unsigned int i) const;

        const std::vector<Antenna>& getAntennas() const;

        void setNetwork(const std::vector<Antenna>& network);

        // view modifiers
        void showAntennas(const bool state);
        void showRanges(const bool state);
        void showColors(const bool state);

        bool shouldShowAntennas() const;
        bool shouldShowRanges() const;
        bool shouldShowColors() const;

	private:
        std::vector<Antenna> m_network;

        bool m_showAntennas;
        bool m_showRanges;
        bool m_showColors;
};

#endif // NETWORK_HPP