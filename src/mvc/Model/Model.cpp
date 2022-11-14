#include "Model.hpp"


Model::Model():
    m_gui(), m_map(), m_network()
{
    
}

Model::~Model() {
    
}

void Model::loadFromConfig(const AppConfig& config) {
    m_map.loadFromConfig(config.map);
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