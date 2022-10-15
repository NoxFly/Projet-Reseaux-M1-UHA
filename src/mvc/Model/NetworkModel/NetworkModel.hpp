#ifndef NETWORKMODEL_HPP
#define NETWORKMODEL_HPP

#include "Model.hpp"
#include "config_interfaces.hpp"

class NetworkModel: public Model {
	public:
		NetworkModel(const NetworkConfig& config);
		~NetworkModel();
};

#endif // NETWORKMODEL_HPP