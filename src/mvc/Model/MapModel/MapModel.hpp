#ifndef MAPMODEL_HPP
#define MAPMODEL_HPP

#include "Model.hpp"
#include "config_interfaces.hpp"

class MapModel: public Model {
	public:
		MapModel(const MapConfig& config);
		~MapModel();
};

#endif // MAPMODEL_HPP