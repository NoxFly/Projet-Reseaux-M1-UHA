#include "Model.hpp"


Model::Model() {
    
}

Model::~Model() {
    
}

void Model::loadFromConfig(const AppConfig& config) {
    m_network.loadFromConfig(config.network);
}

GuiModel Model::getGui() const noexcept {
    return m_gui;
}

MapModel Model::getMap() const noexcept {
    return m_map;
}

NetworkModel Model::getNetwork() const noexcept {
    return m_network;
}