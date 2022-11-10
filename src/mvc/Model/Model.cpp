#include "Model.hpp"


Model::Model() {
    
}

Model::~Model() {
    
}

void Model::loadFromConfig(const AppConfig& config) {
    // TODO : apply the config for the right models
    (void)config;
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