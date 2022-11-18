#ifndef MODEL_HPP
#define MODEL_HPP

#include "MapModel.hpp"
#include "GuiModel.hpp"
#include "NetworkModel.hpp"

#include "config_interfaces.hpp"


class Model {
	public:
        Model();
		~Model();

        void loadFromConfig(AppConfig config);

        GuiModel& getGui() noexcept;
        MapModel& getMap() noexcept;
        NetworkModel& getNetwork() noexcept;

    protected:
        GuiModel m_gui;
        MapModel m_map;
        NetworkModel m_network;
};

#endif // MODEL_HPP