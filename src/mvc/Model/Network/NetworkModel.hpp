#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <vector>
#include <memory>

#include "Antenna/Antenna.hpp"
#include "config_interfaces.hpp"

class NetworkModel {
	public:
		NetworkModel();
		~NetworkModel();

		void loadFromConfig(const NetworkConfig& config);

		Antenna* getAntennaByIndex(const unsigned int i);

        Antenna* operator[](const unsigned int i);

        const std::vector<std::unique_ptr<Antenna>>& getAntennas() const;
        std::vector<std::unique_ptr<Antenna>>& getAntennas();

        void clear();

        // view modifiers
        void showAntennas(const bool state);
        void showRanges(const bool state);
        void showColors(const bool state);

        bool shouldShowAntennas() const;
        bool shouldShowRanges() const;
        bool shouldShowColors() const;

	private:
        void updateColorization();

        std::vector<std::unique_ptr<Antenna>> m_antennas;

        bool m_showAntennas;
        bool m_showRanges;
        bool m_showColors;
};

#endif // NETWORK_HPP