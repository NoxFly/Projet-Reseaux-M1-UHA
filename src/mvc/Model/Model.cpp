#include "Model.hpp"


Model::Model():
    m_gui(), m_map(), m_network()
{
    
}

Model::~Model() {
    
}

void Model::loadFromConfig(const AppConfig& config) {
    // @remark : it's important to load the map first
    // so the antennas in the network have access to the right map's lambert coords & size
    m_map.loadFromConfig(config.map);
    m_network.loadFromConfig(config.network);
}

GuiModel& Model::getGui() {
    return m_gui;
}

MapModel& Model::getMap() {
    return m_map;
}

NetworkModel& Model::getNetwork() {
    return m_network;
}

const GuiModel& Model::getGui() const {
    return m_gui;
}

const MapModel& Model::getMap() const {
    return m_map;
}

const NetworkModel& Model::getNetwork() const {
    return m_network;
}