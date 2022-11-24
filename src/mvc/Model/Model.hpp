#ifndef MODEL_HPP
#define MODEL_HPP

// class Model;

#include "MapModel.hpp"
#include "GuiModel.hpp"
#include "NetworkModel.hpp"

#include "config_interfaces.hpp"

class Model {
	public:
        Model();
		~Model();

        void loadFromConfig(const AppConfig& config);

        GuiModel& getGui();
        MapModel& getMap();
        NetworkModel& getNetwork();

        const GuiModel& getGui() const;
        const MapModel& getMap() const;
        const NetworkModel& getNetwork() const;

    protected:
        GuiModel m_gui;
        MapModel m_map;
        NetworkModel m_network;
};

#endif // MODEL_HPP