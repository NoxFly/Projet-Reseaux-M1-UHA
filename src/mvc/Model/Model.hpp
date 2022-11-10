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

        GuiModel getGui() const noexcept;
        MapModel getMap() const noexcept;
        NetworkModel getNetwork() const noexcept;

    protected:
        GuiModel m_gui;
        MapModel m_map;
        NetworkModel m_network;
};

#endif // MODEL_HPP